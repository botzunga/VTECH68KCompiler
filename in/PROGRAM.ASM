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
t_fichier		dc.b	'AUDIO_5.BIN',0


align
init:
	jsr		beep
	move.l	#$220000,	A0		; Pointeur de l'emplacement du futur fichier
	move.l	#t_fichier,	A1		; Pointeur vers le nom du fichier
	
	;jsr		FASTRAM_ChargeFichier
	;movem.l		A0,-(SP)				; Sauve A0...
	move.l		#$A0000E, A0				; Copie le nom du fichier dans la FastRAM
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	;movem.l		(SP)+,A0				; Restore A0...

	move.b		#3, D0					; Ouvre le fichier
	jsr 		FASTRAM_EnvoieCommande	


	
	;move.b		#4, D0					; Ferme le fichier (si il est A©ventuellement ouvert)
	;jsr 		FASTRAM_EnvoieCommande

	move.l	#$A02000,	A1		;	Adresse de la carte son
	move.l	#$220000,	A0		;	Source des données pour la lecture audio












	jmp		BouclePrincipale
	
	
	
	
	
	
	
_RemplisLeBufferAudio:
	;move.l	#4096,		D4		;	Quantité de données à remplir vers le buffer...
	; Je ne redéfinit pas la valeur D4 car elle est remplie par l'API FASTRAM (de la longuer de la lecture!!)
	
	
_fb_loop:	
	move.b		(A0)+, (A1)		; Copie un octet de A0 vers A1 et incrémente A0 de 1
	cmp.l	#$227AB8,	A0
	bgt		reinitcurseur
	dbra	D4,	_fb_loop
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
	;jsr		_RemplisLeBufferAudio
	jsr		STREAMING_FRAMRemplisLeBuffer
	jmp		BouclePrincipale
	
	
	
		
	
	
	
STREAMING_FRAMRemplisLeBuffer:
	move.b		#5, D0					; Lis le fichier
	jsr 		FASTRAM_EnvoieCommande	
	
	cmp.w		#0,	D4					; Longueur du fichier = 0 ? Probablement  arrivé à la fin du fichier! 
	beq			STREAMING_RetourneAuDebutDuFichier
	
	subi.w		#1,	D4					; DBRA (plus bas est "inclusif"; 0 est aussi traité comme valeur donc il copie bien 4096 octets)
	move.w		D4,	D5					; Sauvegarde de D4, car DBRA va le détruire...

	; **** Partie longue et chiante là où je recopie les données FastRAM ==> Buffer TAMPON Interne *****
	
	move.l		#$A01000,	A1			; Adresse vers le tampon en FastRAM
	move.l		#$220000,	A0			; Adresse du tampon audio
	
_STRMG_CopieVersTampon:
	move.b		(A1)+,	(A0)+	; Copie les données...
	dbra		D5,		_STRMG_CopieVersTampon

	move.w		D4,	D5					; Sauvegarde de D4, car DBRA va le détruire...
		
	; **** Rebelotte mais cette fois-ci, j'envoie les données à la carte SON!
	
	move.l		#$220000,	A0			; Adresse du tampon audio
	
_STRMG_TamponVersAUDIO:	
	move.b		(A0)+, (A1)		; Copie un octet de A0 vers A1 et incrémente A0 de 1
	dbra	D4,	_STRMG_TamponVersAUDIO

	cmp.w		#4095,	D5							; La taille des données lues = 4096 ?
	bne			STREAMING_RetourneAuDebutDuFichier	; Si NON, on est a la fin du fichier => REVIENS AU DEBUT (FileSEEK)
	
	; **** DONE ! ****

	rts

STREAMING_RetourneAuDebutDuFichier:
	move.b		#8, D0					; Remets la lecture du fichier à 0
	move.l		#0,	D1			
	jsr 		FASTRAM_EnvoieCommande
	rts
	
	
FSTRAM_OuvreFichierSTREAMING:				; *** Ouvre le fichier en LECTURE *** 
	move.l		#$A0000E, A0				; Copie le nom du fichier dans la FastRAM
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+

	move.b		#3, D0						; Ouvre le fichier
	jsr 		FASTRAM_EnvoieCommande	
	rts
	
FSTRAM_FermeFichierSTREAMING
	move.b		#4, D0					; Ferme le fichier (si il est A©ventuellement ouvert)
	jsr 		FASTRAM_EnvoieCommande	
	rts
	
	
	
	
