; 	VTECH keyboard libary - Alexandre BOTZUNG (Dec. 2018)
;	-----------------------------------------------------	
;	Permet de lire et de piloter les diodes du clavier et de la souris.
;	Permet aussi de lire les frappes sur le clavier.
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

; === Table des caractères du clavier ANGLAIS ===

tbl_lcase0	dc.b	 $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
tbl_lcase1	dc.b	 $00, $00, $00, $00, $00, $00, $00, $60, $5D, $3D, $2D, $27, $5B, $3B, $70, $2F
tbl_lcase2	dc.b	 $30, $0D, $08, $6C, $6F, $39, $00, $5C, $00, $00, $00, $2E, $27, $6B, $69, $00
tbl_lcase3	dc.b	 $38, $1B, $6D, $6A, $75, $37, $00, $00, $00, $00, $00, $00, $6E, $68, $79, $00
tbl_lcase4	dc.b	 $36, $09, $62, $67, $74, $35, $00, $00, $00, $00, $00, $20, $76, $66, $72, $00
tbl_lcase5	dc.b	 $34, $63, $64, $65, $33, $00, $00, $00, $00, $78, $73, $77, $32, $00, $00, $00
tbl_lcase6	dc.b	 $00, $00, $00, $7A, $61, $71, $31, $00, $00, $00, $2E, $2F, $2A, $2D, $2B, $0D
tbl_lcase7	dc.b	 $30, $31, $32, $33, $34, $35, $36, $37, $38, $39, $00, $00, $00, $00, $00, $00

tbl_ucase0	dc.b	 $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
tbl_ucase1	dc.b	 $00, $00, $00, $00, $00, $00, $00, $7E, $7D, $2B, $5F, $22, $7B, $3A, $50, $3F
tbl_ucase2	dc.b	 $29, $0D, $08, $4C, $4F, $28, $00, $7C, $00, $00, $00, $3E, $3C, $4B, $49, $00
tbl_ucase3	dc.b	 $2A, $1B, $4D, $4A, $55, $26, $00, $00, $00, $00, $00, $00, $4E, $48, $59, $00
tbl_ucase4	dc.b	 $5E, $09, $42, $47, $54, $25, $00, $00, $00, $00, $00, $20, $56, $46, $52, $00
tbl_ucase5	dc.b	 $24, $43, $44, $45, $23, $00, $00, $00, $00, $58, $53, $57, $40, $00, $00, $00
tbl_ucase6	dc.b	 $00, $00, $00, $5A, $41, $51, $21, $00, $00, $00, $2E, $2F, $2A, $2D, $2B, $0D
tbl_ucase7	dc.b	 $30, $31, $32, $33, $34, $35, $36, $37, $38, $39, $00, $00, $00, $00, $00, $00

KEYBOARD_STATUS	dc.b	0	; Gère le status de CAPS LOCK (bit2) et NUM LOCK (bit1)


InitKbd:
		ori.b		#8,($600501).l
		move.b		#0,KEYBOARD_STATUS
		move.b		KEYBOARD_STATUS,D0
		;jsr			SendKbdLed
		rts

FreeKbd:
		andi.b		#$F7,($600501).l
		rts

SendKbdLed:
		ori.b		#8,($600501).l
		movem.l 	D0,-(SP)
		move.b		#$F9,D0
		jsr			SendKbdCmd
		movem.l		(SP)+,D0
		jsr			SendKbdCmd	
		rts
		
SendKbdCmd:
		move.b		d0,($600301).l
		jsr			delay
		rts
		
Inkey:
		
		;D1 A0
		; Renvoie la tocuhe dans D0 (00 si il n'y a rien)
		move.w	($600300),D0
		btst	#$F,D0  ; Teste "erreur de parité"
		bne		inkey_nobtn			; bit=1? => ERREUR DE PARITE
		btst	#$C,D0  ; Teste le bit "Trame SOURIS ou CLAVIER?"
		bne		inkey_nobtn			; bit=1 ? => TRAME POUR LA SOURIS 
		btst	#$8,D0  ; Teste le bit "Trame valide ?"
		bne 	inkey_nobtn			; bit=1 ? => TRAME INVALIDE
		btst	#$7,D0  ; Teste le bit "Touche pressé"
		bne		inkey_nobtn			; bit=0 ? => Pas de touche pressé!
		
		cmp		#$16,D0	; **SPECIAL** Arret du jouet
		beq		inkey_shutdown
		
		cmp		#$47,D0	; **SPECIAL** Bascule CAPS LOCK
		beq		inkey_capslk
	
		movem.l 	D1/A0,-(SP)
		;jsr		beep

		move.b	KEYBOARD_STATUS,D1 ; Choisis quel table à prendre minuscule/MAJUSCULE
		btst	#2,D1
		beq		ikey_lcase
		jmp		ikey_ucase
ikey_lcase:
		move.l	#tbl_lcase0,D1
		jmp		ikey_caseend
ikey_ucase:
		move.l	#tbl_ucase0,D1
ikey_caseend:
		
			; Charge la table clavier
		andi.l	#$7F,D0  ; Garde que les bits des touches
		add.l	D0,D1  ; Fait le décalage
		movea.l	D1,A0  ; Déplace le résultat dans A0
		
		
inkey_debe:
		move.w	($600300),D0
		btst	#$7,D0  ; Teste le bit "Touche pressé"
		beq		inkey_debe		; bit=0 ? => Pas de touche pressé!		
		
		move.b	(A0),D0  ; Copie le caractère dans D0
		
		movem.l		(SP)+,D1/A0
		rts

inkey_debounce:
		move.w	($600300),D0
		btst	#$7,D0  ; Teste le bit "Touche pressé"
		beq		inkey_debounce		; bit=0 ? => Pas de touche pressé!	
		move.b	#0,D0
		rts
	
inkey_shutdown:
		move.b	#0,($600801)
		jmp		inkey_shutdown

inkey_capslk:
		move.b	KEYBOARD_STATUS,D0
		btst	#2,D0
		beq		ikeycplk_on
		
		and.b	#$FB,D0 
		move.b	D0,KEYBOARD_STATUS
		jsr		SendKbdLed
		jmp		inkey_debounce
		
		
ikeycplk_on:
		or.b	#$04,D0
		move.b	D0,KEYBOARD_STATUS
		jsr		SendKbdLed
		jmp		inkey_debounce


inkey_nobtn:
		move.b	#0,D0
		
		rts
