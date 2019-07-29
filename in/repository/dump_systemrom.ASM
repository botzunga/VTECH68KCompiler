;	PROGRAMME v0.1
	org         $00210000
	jmp			init
	include		vtech_videoconsole.inc
	include		vtech_fastram.inc
	include 	vtech_common.inc
	include 	vtech_keyboard.inc	
; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	


;t_banner		dc.b	'Hello world pour un test !!',0
t_fichier		dc.b	'DUMP.BIN',0

align
init:
	move.l		#0,	A5					; configure A3 (pointeur d'adresse pour la memoire ROM)
	move.b		#4, D0					; Ferme le fichier (si il est éventuellement ouvert)
	jsr 		FASTRAM_EnvoieCommande
	
	move.l		#t_fichier,	A1  		; Le Fichier a envoyer
	move.l		#FTRAM_c_TEXT, A0		; Copie le nom du fichier dans la FastRAM
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	move.l		(A1)+, (A0)+
	

	move.b		#3, 	D0					; Ouvre le fichier...
	move.w		#$42,	D3					; ...en ecriture
	jsr 		FASTRAM_EnvoieCommande	
	
	
	move.l		#511,	D1
doloopinit:
	move.l		#$A01000,	A4					; Pointeur pour la FRAM
	move.l		#2048,	D0						; NBR de fois que je le fais (2048x2 =4096 octets)
	
doloop:
	move.w		(A5)+, (A4)+
	dbra.w		D0,	doloop
	
	move.b		#6, 	D0					; Ecris vers le fichier
	move.w		#4096,	D3					; 4096 octets
	jsr 		FASTRAM_EnvoieCommande		
	dbra.w		D1,		doloopinit			; Compte 512 fois l'envoi (512*4096=2 Mo)
	
	move.b		#4, D0					; Ferme le fichier (si il est eventuellement ouvert)
	jsr 		FASTRAM_EnvoieCommande
	
	jsr			beep
	jsr			halt					; Fin!