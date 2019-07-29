; 	VTECH FastRAM! libary - Alexandre BOTZUNG (Dec. 2018)
;	-----------------------------------------------------	
;	Permet de piloter la liaison FastRAM! <-> Arduino et de réaliser des appels externes
;
;
;	Permission to use, copy, modify, and/or distribute this software for any
;	purpose with or without fee is hereby granted, provided that the above
;	copyright notice and this permission notice appear in all copies.
;
;	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
;	REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
;	FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
;	INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
;	LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
;	OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
;	PERFORMANCE OF THIS SOFTWARE. 
;
; !!! NECESSITE QUE FTRAM_xxx DOIVENT ETRES EN RAM !!! (voir org $...)
; !!! N ECRIRE QUE VERS FASTRAM EN WORD OU LONG !!! _PAS_ EN BYTE !!!
; 
;	--- Variable de commande / réponse 
FTRAM_w_CMDRES	EQU		$A00000 ; base  0 (w=>+2)
;	--- Variable LONGA
FTRAM_l_LONGA	EQU		$A00002 ; base  2 (l=>+4)
;	--- Variable LONGB
FTRAM_l_LONGB	EQU		$A00006 ; base  6 (l=>+4)
;	--- Variable WORDA
FTRAM_w_WORDA	EQU		$A0000A ; base  A (w=>+2)
;	--- Variable WORDB
FTRAM_w_WORDB	EQU		$A0000C ; base  C (w=>+2)
;	--- Variable TEXTE ( !!! N EXCRIRE QUE VERS FASTRAM EN WORD OU LONG !!! _PAS_ EN BYTE !!!)
FTRAM_c_TEXT	EQU		$A0000E ; base  E (text{$C}=> next base :$1A)
;   --- Pointeur vers HIRAM
FTRAM_ptr_HIRAM EQU		$A01000

FASTRAM_ChargeFichier:
	; Charge un fichier à l'adresse A0
	; Le nom du fichier est pointée par A1
	; Le status est dans D0 (1=si erreur/0=OK)
	movem.l D0-D4/A0-A1,-(SP)	
	
	move.b		#4, D0					; Ferme le fichier (si il éventuellement ouvert)
	jsr 		FASTRAM_EnvoieCommande
	
	movem.l		A0,-(SP)				; Sauve A0...
	move.l		#FTRAM_c_TEXT, A0		; Copie le nom du fichier dans la FastRAM
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	movem.l		(SP)+,A0				; Restore A0...

	move.b		#3, D0					; Ouvre le fichier
	jsr 		FASTRAM_EnvoieCommande	
	
	cmp.b		#1,	D0					; Il y a eu un problème ?
	beq			_FRChERR
	
_FRCFLisBoucle:
	move.b		#5, D0					; Lis le fichier
	jsr 		FASTRAM_EnvoieCommande	
	
	cmp.b		#1,	D0					; Il y a eu un problème ?
	beq			_FRChERR	
	
	cmp.w		#0,	D4					; Lecture du fichier = 0 ? 
	beq			_FRChOK
	
	subi.w		#1,	D4					; DBRA (plus bas est "inclusif"; 0 est aussi traité comme valeur donc il copie bien 4096 octets)
	move.w		D4,	D0					; Garde le registe WORDB dans D0
	
	
	
	move.l		#FTRAM_ptr_HIRAM,	A1
	
_FRCFCopie:
	move.b		(A1)+,	(A0)+	; Copie les données...
	dbra		D4,		_FRCFCopie
	
	cmp.w		#4095,	D0				; La taille des données lues = 4096 ?
	beq			_FRCFLisBoucle			; Si OUI alors continue la lecture!
										; Sinon, la lecture est terminée!
	
	jmp			_FRChOK
_FRChERR:
	movem.l (SP)+,D0-D4/A0-A1
	move.b		#1,	D0
	jmp			_FRChEND
_FRChOK:
	movem.l (SP)+,D0-D4/A0-A1
	move.b		#0,	D0
_FRChEND:
	rts

FASTRAM_EnvoieCommande:
	; Utilise D0.b pour la commande, renvoie D0.b pour le status
	; Utilise D1.l comme "variable de travail"
	
	; PROCESS : 1. ecrire la commande
	jsr			LeveSemaphore
	move.w		D0,		(FTRAM_w_CMDRES)
	move.l		D1,		(FTRAM_l_LONGA)
	move.w		D3,		(FTRAM_w_WORDA)
	jsr			BaisseSemaphore
	
	; PROCESS : 2. Attendre la réponse de l'arduino
	jsr			AttenteSemaphoreARDUINO
	
	; PROCESS : 3. Récupération de la valeur
	move.w		(FTRAM_w_CMDRES),D0
	move.l		(FTRAM_l_LONGA),D1
	move.l		(FTRAM_l_LONGB),D2
	move.w		(FTRAM_w_WORDA),D3
	move.w		(FTRAM_w_WORDB),D4
	rts
	
LeveSemaphore:
	move.b		#1,			($600101)		; Semaphore : Vtech PREND le controle
	rts
BaisseSemaphore:
	move.b		#0,			($600101)		; Semaphore : Vtech PREND le controle
	rts
; === Attends la réponse de l'arduino. Je cherche à voir un front montant.
AttenteSemaphoreARDUINO:
	;TODO : Ajouter un timeout!!!
	movem.l 	D0,-(SP)
_attsemaardone
	move.b		($600803),	D0 				; Attends que l'arduino PRENDS la main / lis le port cartouche
	cmp.b		#0,			D0				; Si =0 attends dans le vide (Arduino a pris la main)
	beq			_attsemaardone
_attsemaard:
	move.b		($600803),	D0 				; Attends que l'arduino LACHE la main / lis le port cartouche
	cmp.b		#0,			D0				; Si <>0 attends dans le vide (Arduino a pris la main)
	bne			_attsemaard
	movem.l 	(SP)+,D0
	rts