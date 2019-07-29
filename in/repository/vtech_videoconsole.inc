; 	VTECH Video Console - Alexandre BOTZUNG (Dec. 2018)
;	--------------------------------------------------- 	
;	Permet d'afficher du texte sur l'ecran bitmap du Genius PC
;	-> Dimension de la console texte : 46(X) x 23(Y)
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
; !!! NECESSITE QUE CONSOLE_xxx DOIVENT ETRES EN RAM !!! (voir org $...)

;	=== Coordonnées du curseur texte (en pixels)
CONSOLE_X		dc.w	$0   
CONSOLE_Y		dc.w	$0   
;	=== Attributs de couleurs utilisés par le pinceau/sprite (16 couleurs)
CONSOLE_COLOR	dc.b	$1   
CONSOLE_BGCOL	dc.b	$4   
;	=== Pointeur mémoire vers la banque des sprites
CONSOLE_FONT	dc.l	$00141986   
;	=== Variables internes
CONSOLE_CHAR	dc.b	$0   
CONSOLE_TEXT	dc.l	$0   
;
;	--- APPELS ---
;
;	DrawText	 - Affiche une chaine de texte à l'écran
;				   Utilise le pointeur (CONSOLE_TEXT) pour afficher le texte à l'écran.
;
;	DrawChar   	 - Affiche un caractère à l'écran
;				   Utilise la variable CONSOLE_CHAR et affiche son contenu à l'écran.
;
;	ClearScreen  - Efface l'écran avec la couleur dans CONSOLE_BGCOL 
;
;	DrawHex		 - Affiche le registre D0.l en Hexadecimal à l'écran
;
;	WaitVSYNC	 - Attends le top synchronisation. (taux de rafraichissement de l'écran : 50Hz)

WaitVSYNC:
		; Attends le top synchro vidéo. Utile pour réaliser des timers "pas cher" (rafraichissement vidéo à 50Hz)
		movem.l	D0-D1,-(SP)
		move.b	($601009),	D0
		andi.l	#4,			D0
		moveq	#4,			D1
		cmp.l	D0,			D1
		bne.s	WaitVSYNC
_vvsync:
		btst	#2,			($601009)
		bne.s	_vvsync
		movem.l	(SP)+,D0-D1,
		rts

DrawHex:
	; Le chiffre à afficher est dans D0 ; explose le registre D1 et D2
		movem.l 	D1-D2,-(SP)
		move.l		#7,			D2
_dhsrt:
		rol.l		#4,			D0 ; Décale de 4 bits vers la gauche D0
		move.l		D0,			D1 ; Copie l'octet (de droite) dans D1
		and.l		#$0F,		D1 ; Garde que la partie basse de D1
		cmp.b		#10,		D1 ; Compare D1 et 9
		blt			_dnohex	   ; Si il est plus petit que 10, on reste sur les chiffres
_dhex:
		add.b		#7,		D1 ; Ajoute 65 pour se décaler sur la table des lettres (-10 car la valeur est supérieur à 9) (7=65-10-48)
_dnohex:
		add.b		#48,	D1
		move.b		D1,		CONSOLE_CHAR
		jsr			DrawChar
		dbra		D2,		_dhsrt
		movem.l 	(SP)+,D1-D2
		rts

DrawText:
		;On admet que CONSOLE_TEXT est peuplé _X et _Y aussi.
		movem.l 	D0,-(SP)
		movea.l		CONSOLE_TEXT,		A0
loopdchar:
		move.b		(A0)+,	D0 ; Charge le caractère en memoire
		cmp.b		#0,				D0 ; {CHAR} = 0 ? 
		beq			enddtext
		move.b		D0,				CONSOLE_CHAR
		jsr			DrawChar		   ; Dessine le char a l'écran
		jmp			loopdchar
enddtext:
		movem.l 	(SP)+,D0
		rts
		
	
ClearScreen:
		clr.w	(CONSOLE_X)
		clr.w	(CONSOLE_Y)
		move.l		#$00300000,	A1				; Zone d'arrivée
		move.b	(CONSOLE_BGCOL),D1	; Avec le nibble dans D1
	
		move.b	D1,		D3
		rol.b	#4,		D3 ; rotate left 4 bits D3 (nibble bas devient haut)
		or.b	D1,		D3 ; combine nibble bas et haut 
		move.b	D3,		D2 ; BYTE 0 = Col
		rol.l	#8,		D2
		move.b	D3,		D2 ; BYTE 0 = Col
		rol.l	#8,		D2
		move.b	D3,		D2 ; BYTE 0 = Col
		rol.l	#8,		D2
		move.b	D3,		D2 ; BYTE 0 = Col
		move.l	D2,		D1
		move.l		#$3FFF,		D0
pnt2	move.l		D1,		(A1)+  			; Les écritures vers la mémoire DOIT ETRE fait en 16 bits!
		dbra		D0,			pnt2	
		rts	

ClearScreenAlternate:
		move.l		#$00310000,	A1				; Zone d'arrivée
		move.b	(CONSOLE_BGCOL),D1	; Avec le nibble dans D1
	
		move.b	D1,		D3
		rol.b	#4,		D3 ; rotate left 4 bits D3 (nibble bas devient haut)
		or.b	D1,		D3 ; combine nibble bas et haut 
		move.b	D3,		D2 ; BYTE 0 = Col
		rol.l	#8,		D2
		move.b	D3,		D2 ; BYTE 0 = Col
		rol.l	#8,		D2
		move.b	D3,		D2 ; BYTE 0 = Col
		rol.l	#8,		D2
		move.b	D3,		D2 ; BYTE 0 = Col
		move.l	D2,		D1
		move.l		#$3FFF,		D0
pnt2al	move.l		D1,		(A1)+  			; Les écritures vers la mémoire DOIT ETRE fait en 16 bits!
		dbra		D0,			pnt2al	
		rts	
		
; Dessine juste un CHAR à l'écran
DrawChar	movem.l D0-D6/A0-A2,-(SP)
	move.b	(CONSOLE_COLOR),($60101F) ; Couleur du sprite
	move.b	(CONSOLE_BGCOL),($60101D) ; Couleur de fond
	;move.l	(CONSOLE_FONT),	($600606) ; Configure la police d'écriture
	move.b	(CONSOLE_CHAR),	D1
	cmp.b	#$0D,		D1
	beq		.dcharnewline   ; Chr(13) => Carriage return
	cmp.b	#10,		D1
	beq		.dcharend		; Chr(10) => OSEF
	move.w	(CONSOLE_X), D0
	cmp.w	#500, D0
	bge		.dcharnewline
	bra.s	.dcharnonewline
.dcharnewline
	;Genere une nouvelle ligne
	move.w	#0,	(CONSOLE_X) ; CONSOLE X
	move.w	(CONSOLE_Y), D0 ; CONSOLE Y
	add.w	#11, D0
	move.w	D0,	(CONSOLE_Y) ; CONSOLE Y
	cmp.b	#13,	D1	  ; Chr(13) => Juste NEWLINE!
	beq		.dcharend
.dcharnonewline
	;TODO Comparer CONSOLE Y au maximum et generer un scroll software!
	move.w	(CONSOLE_Y),	D0
	cmp.w	#$FB,		D0
	bge		.dcharscroll
	bra.s	.dcharnoscroll
.dcharscroll
	;1. Scroll le texte à l'écran.
	move.l	#$300B00, A0 ; 256*11
	move.l	#$300000, A1
	move.l	#$3D3F,	  D2 ; =($FFFF(1 ecran) - $B00(=256vertical*11lignes)/4(move.LONG)
.dcharscrollloop	
	;move.l	#$300B00, A0 ; 256*11
	move.l	(A0)+,		(A1)+
	dbra	D2,			.dcharscrollloop
	;2. Effacement de la ligne
	;2.1 Peuplement de D2 avec le nibble couleur
	move.b	(CONSOLE_BGCOL),D1	; Avec le nibble dans D1
	move.b	D1,		D3
	rol.b	#4,		D3 ; rotate left 4 bits D3 (nibble bas devient haut)
	or.b	D1,		D3 ; combine nibble bas et haut 
	move.b	D3,		D2 ; BYTE 0 = Col
	rol.l	#8,		D2
	move.b	D3,		D2 ; BYTE 0 = Col
	rol.l	#8,		D2
	move.b	D3,		D2 ; BYTE 0 = Col
	rol.l	#8,		D2
	move.b	D3,		D2 ; BYTE 0 = Col
	move.l	D2,		D3
.dcharpvar
	move.l	#$30F500, A0 ; $FFFF-($FFFF-$B00)
	move.l	#$02BF,	  D2 ; $B00/4(long)
.dcharscrollclearloop	
	move.l	D3,		  (A0)+
	dbra	D2, .dcharscrollclearloop
	move.w	#$F3,	  (CONSOLE_Y)
.dcharnoscroll
	move.w	(CONSOLE_X),	($601018) ; Configure X
	move.w	(CONSOLE_Y),	($60101A) ; Configure Y
	move.b	(CONSOLE_CHAR),	D1
	move.b	D1,	($60060B)	; Affiche le caractere!
.dwtchardrw
	move.b	($601011).l,	D0
	andi.b	#2,				D0
	bne		.dwtchardrw
	move.w	(CONSOLE_X), D0 ; CONSOLE X
	add.w	#11, D0
	move.w	D0,	(CONSOLE_X) ; CONSOLE X
.dcharend
	movem.l (SP)+,D0-D6/A0-A2
	rts