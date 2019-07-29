;	PROGRAMME v0.1
	org         $00210000
	jmp			init
	include		vtech_videoconsole.inc
	include		vtech_fastram.inc
	include 	vtech_common.inc
	include 	vtech_keyboard.inc	
	
	; $A0 0000 => ZONE FRAM
	; $A0 2000 => Sound FIFO
	; $A0 4001 => Sound Buffer status (D0) (1=Si le buffer est rempli en DESSOUS de 50% / 0= Si il est rempli AU DESSUS de 50%
; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	


;t_banner		dc.b	'Hello world pour un test !!',0
t_fichier		dc.b	'AUDIO.BIN',0


align
init:
	jsr		beep
	move.l	#$220000,	A0		; Pointeur de l'emplacement du futur fichier
	move.l	#t_fichier,	A1		; Pointeur vers le nom du fichier
	
	jsr		FASTRAM_ChargeFichier
	
	
	move.b		#4, D0					; Ferme le fichier (si il est A©ventuellement ouvert)
	jsr 		FASTRAM_EnvoieCommande

	move.l	#$A02000,	A1		;	Adresse de la carte son
	move.l	#$220000,	A0		;	Source des données pour la lecture audio












	jmp		BouclePrincipale
	
_ReplisLeBufferAudio:
	move.l	#4096,		D1		;	Quantité de données à remplir vers le buffer...
	
_fb_loop:	
	move.b		(A0)+, (A1)		; Copie un octet de A0 vers A1 et incrémente A0 de 1
	cmp.l	#$227AB8,	A0
	bgt		reinitcurseur
	dbra	D1,	_fb_loop
	rts
	
reinitcurseur:
	move.l	#$220000,	A0		;	Source des données pour la lecture audio
	jmp		reinitcurseur       ;	BLOCAGE LECTURE
	
	rts
	
BouclePrincipale:
	move.b	($A04001),	D0
	and.b	#1,	D0			;	D0 = D0 AND 0b0000 0001 (récupère le drapeau)
	cmp.b	#1,	D0			; 	CoMPare D0 et 1
	bne		BouclePrincipale;	<> 1 ? ==> Va à BouclePrincipale. (car Buffer PLEIN)
							;	...sinon RemplisLeBuffer!
	jsr		_ReplisLeBufferAudio
	jmp		BouclePrincipale
	
	
	
	
STREAMING_FRAMRemplisLeBuffer:





	rts
	
	
	
	
	
	
	
	
	
	
	
	
	
boucle:
	;Rappel: BEQ (branch si bit=0) / BNE (branch si bit=1)
	move.w	($600300),	D0
	btst	#$F,		D0  ; Teste "erreur de parité"
	bne		boucle			; bit=1? => ERREUR DE PARITE
	btst	#$C,		D0  ; Teste le bit "Trame SOURIS ou CLAVIER?"
	bne		boucle			; bit=1 ? => TRAME POUR LA SOURIS 
	btst	#$8,		D0  ; Teste le bit "Trame valide ?"
	bne 	boucle			; bit=1 ? => TRAME INVALIDE
	btst	#$7,		D0  ; Teste le bit "Touche pressé"
	bne		boucle			; bit=0 ? => Pas de touche pressé!
	
	; Ici je devrais récupérer mon scan code pour la touche.
	;move.b	D0,			D1
	jsr		DrawHex
	
	move.l	#t_fichier,CONSOLE_TEXT
	jsr		DrawText	
	
debounce:
	move.w	($600300),	D0
	btst	#$7,		D0  ; Teste le bit "Touche pressé"
	beq		debounce		; bit=0 ? => Pas de touche pressé!	
	
	jmp		boucle
	