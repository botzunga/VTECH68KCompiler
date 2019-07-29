; VTECH GeniusIQ PCRamdisk - Alex BOTZUNG (Jan 2019)
;
;
; Protocole :
; -> Lors du démarrage du programme, le programme sers la main à l'arduino (lui indiquant qu'il est prêt à fonctionner)
; -> Puis le programme PC attends dans une boucle toute commande via le port série.
;    !!! Les commandes possèdent des longueurs variables !!!
PortCOM$="COM3"
Maison$=GetCurrentDirectory()+"DISK\"
*Buffy=AllocateMemory(1)
*HEADER_buffer=AllocateMemory(32)
*DATA_buffer=AllocateMemory(4096)

#FRAM_CMDRES=0
#FRAM_LONGA=2
#FRAM_LONGB=6
#FRAM_WORDA=$A
#FRAM_WORDB=$C




Procedure Quitte()
  PrintN("Presse ENTREE pour quitter.")
  dummy$=Input()
  End
EndProcedure
Procedure MSG_ERREUR(LeTexte$)
  ConsoleColor(15,12)
  PrintN(LeTexte$)
  ConsoleColor(7,0)   
EndProcedure
Procedure MSG_INSTRUCTION(LeTexte$)
  ConsoleColor(0,14)
  PrintN(LeTexte$)
  ConsoleColor(7,0)   
EndProcedure
Procedure MSG_DEBUG(LeTexte$,Tipe)
  If Tipe=1
    ConsoleColor(13,0)
    Print(LeTexte$+" ")
    PrintN("")
    ConsoleColor(7,0)   
  Else
    ConsoleColor(13,0)
    Print(LeTexte$+" ")
    ConsoleColor(7,0)  
  EndIf
EndProcedure
Procedure MSG_VERT(LeTexte$)
  ConsoleColor(2,0)
  PrintN("["+LeTexte$+"]")
  ConsoleColor(7,0)   
EndProcedure
Procedure MSG_ROUGE(LeTexte$)
  ConsoleColor(4,0)
  PrintN("["+LeTexte$+"]")
  ConsoleColor(7,0)   
EndProcedure
Procedure Active_mode_PCRAMDISK()
  ;Sert la main à l'arduino
  *Buffy_TEMP=AllocateMemory(1)
  While(AvailableSerialPortInput(0)>0)   ; Vide le buffer...
    ReadSerialPortData(0,*Buffy_TEMP, 1)
  Wend
  Delay(1000)

  PokeA(*Buffy_TEMP, 'A'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture 
  While(timeout<1100)
    Delay(1)
    If AvailableSerialPortInput(0)>0 ; Des données sont arrivés!
      ReadSerialPortData(0,*Buffy_TEMP, 1)
      timeout=0
      Break
    EndIf
    If timeout=999
      PrintN("[PCRD] - (Active_mode_PCRAMDISK) TIMEOUT -> L'arduino ne réponds pas.")
    EndIf
    timeout+1
  Wend
  If PeekA(*Buffy_TEMP)='A'
    PrintN("[PCRD] - (Active_mode_PCRAMDISK) Arduino OK. Bascule en mode PCRamdisk")
  Else
    PrintN("[PCRD] - (Active_mode_PCRAMDISK) Erreur ; mauvaise réponse de l'Arduino!;"+Str(PeekA(*Buffy_TEMP)))
  EndIf
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure Desactive_mode_PCRAMDISK()
  ;Sert la main à l'arduino
  *Buffy_TEMP=AllocateMemory(1)
  While(AvailableSerialPortInput(0)>0)
    ReadSerialPortData(0,*Buffy_TEMP, 1)
  Wend
  Delay(1000)

  PokeA(*Buffy_TEMP, 'a'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture 
  While(timeout<1100)
    Delay(1)
    If AvailableSerialPortInput(0)>0 ; Des données sont arrivés!
      ReadSerialPortData(0,*Buffy_TEMP, 1)
      timeout=0
      Break
    EndIf
    If timeout=999
      PrintN("[PCRamdisk] - (Desactive_mode_PCRAMDISK) TIMEOUT -> L'arduino ne réponds pas.")
    EndIf
    timeout+1
  Wend
  If PeekA(*Buffy_TEMP)='a'
    PrintN("[PCRamdisk] - (Desactive_mode_PCRAMDISK) Arduino OK. Bascule en mode PCRamdisk")
  EndIf
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure FASTRAM_BUFFER_to_UART(*LeBuffer)
  ;Dump 4096 bytes from BUFFER
  *Buffy_TEMP=AllocateMemory(1)
  Timeout=0
  PokeA(*Buffy_TEMP, 'o'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande de lecture
  While(AvailableSerialPortInput(0)<>4096)
    Delay(1)
    Timeout+1
    If Timeout>3000
      Debug "[FASTRAM] - Reader error! (TIMEOUT)"
      Debug AvailableSerialPortInput(0)
      Break ;from While
    EndIf
  Wend 
  If Timeout<3000:ReadSerialPortData(0,*LeBuffer, 4096):EndIf ; Vide le buffer de lecture
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure PCRD_UART_to_BUFFER(*LeBuffer)
  ;Write 4096 bytes to BUFFER
  Shared *MEMBuff
  *Buffy_TEMP=AllocateMemory(1)
  ;PokeA(*Buffy_TEMP, 'i'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture  
  ReadSerialPortData(0,*Buffy_TEMP,1)
  If PeekA(*Buffy_TEMP)<>'i'
    MSG_ERREUR("FASTRAM_UART_to_BUFFER - Mauvais octet de synchronisation!")
  EndIf
  ;Delay(5)
  Curr=0
  For y=0 To 127
    WriteSerialPortData(0, *LeBuffer+curr, 32) ; 16 mots
    Curr+32
    ReadSerialPortData(0,*Buffy_TEMP, 1) ; Attends la réponse...
    If PeekA(*Buffy_TEMP)<>'!'
      MSG_ERREUR("[PCRD] - Writer ERROR! page: "+Str(y))
    Else
      ;Debug "[FASTRAM] - Write page: "+Str(y)
    EndIf
  Next
  ;MSG_DEBUG("[PCRD] - Writer done.",1)
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure FASTRAM_BUFFER_to_LOSRAM()
  *Buffy_TEMP=AllocateMemory(1)
  PokeA(*Buffy_TEMP, '>'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture   
  While(AvailableSerialPortInput(0)<>1)
    Delay(1)
    Timeout+1
    If Timeout>3000
      Debug "[FASTRAM] - BUFFER to LOSRAM error! (TIMEOUT)"
      Debug AvailableSerialPortInput(0)
      Break ;from While
    EndIf
  Wend 
  If Timeout<3000
    ReadSerialPortData(0,*Buffy_TEMP,1)
    If PeekA(*Buffy_TEMP)<>'>'
      Debug "[FASTRAM] - Mauvaise réponse pour BUFFER to LOSRAM!"
    Else
      Debug "[FASTRAM] - BUFFER to SRAM ok!"
    EndIf
  EndIf
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure FASTRAM_BUFFER_to_HISRAM()
  *Buffy_TEMP=AllocateMemory(1)
  PokeA(*Buffy_TEMP, '*'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture   
  While(AvailableSerialPortInput(0)<>1)
    Delay(1)
    Timeout+1
    If Timeout>3000
      Debug "[FASTRAM] - BUFFER to HISRAM error! (TIMEOUT)"
      Debug AvailableSerialPortInput(0)
      Break ;from While
    EndIf
  Wend 
  If Timeout<3000
    ReadSerialPortData(0,*Buffy_TEMP,1)
    If PeekA(*Buffy_TEMP)<>'*'
      Debug "[FASTRAM] - Mauvaise réponse pour BUFFER to HISRAM!"
    Else
      Debug "[FASTRAM] - BUFFER to SRAM ok!"
    EndIf
  EndIf
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure FASTRAM_LOSRAM_to_BUFFER()
  *Buffy_TEMP=AllocateMemory(1)
  PokeA(*Buffy_TEMP, '<'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture   
  While(AvailableSerialPortInput(0)<>1)
    Delay(1)
    Timeout+1
    If Timeout>3000
      Debug "[FASTRAM] - LOSRAM to BUFFER error! (TIMEOUT)"
      Debug AvailableSerialPortInput(0)
      Break ;from While
    EndIf
  Wend 
  If Timeout<3000
    ReadSerialPortData(0,*Buffy_TEMP,1)
    If PeekA(*Buffy_TEMP)<>'<'
      Debug "[FASTRAM] - Mauvaise réponse pour LOSRAM to BUFFER!"
    Else
      Debug "[FASTRAM] - SRAM to BUFFER ok!"
    EndIf
  EndIf
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure FASTRAM_HISRAM_to_BUFFER()
  *Buffy_TEMP=AllocateMemory(1)
  PokeA(*Buffy_TEMP, '%'):WriteSerialPortData(0,*Buffy_TEMP,1)  ; Envoie la commande ecriture   
  While(AvailableSerialPortInput(0)<>1)
    Delay(1)
    Timeout+1
    If Timeout>3000
      Debug "[FASTRAM] - HISRAM to BUFFER error! (TIMEOUT)"
      Debug AvailableSerialPortInput(0)
      Break ;from While
    EndIf
  Wend 
  If Timeout<3000
    ReadSerialPortData(0,*Buffy_TEMP,1)
    If PeekA(*Buffy_TEMP)<>'%'
      Debug "[FASTRAM] - Mauvaise réponse pour HISRAM to BUFFER!"
    Else
      Debug "[FASTRAM] - HISRAM to BUFFER ok!"
    EndIf
  EndIf
  FreeMemory(*Buffy_TEMP)
EndProcedure
Procedure EnvoieJusteHEADER()
  Shared  *Buffy
  Shared *HEADER_buffer
  PokeA(*Buffy, 'X')
  WriteSerialPortData(0, *Buffy, 1)
  WriteSerialPortData(0, *HEADER_buffer,32)
EndProcedure
Procedure.q BUFFER_ReadLong(position, *LeBuffer)
  If Int(Mod(position, 2))=1
    MSG_ERREUR("BUFFER_ReadLong - Adresse IMPAIRE!")
  EndIf
  ProcedureReturn PeekU(*LeBuffer+position)<<16+PeekU(*LeBuffer+position+2)
EndProcedure
Procedure BUFFER_WriteLong(position, *LeBuffer, Valeur.l)
  PokeU(*LeBuffer+position, Valeur>>16)
  PokeU(*LeBuffer+position+2, Valeur & $0000FFFF)
EndProcedure

Procedure.s PCRD_LisFichier(*Buffer)
  LeFichier.s=""
  DrapeauFin=0
  ;$E
  For x=1 To 12  ; 12=>"DEADFOOD.ABC"
    If Int(Mod(x,2))=1 ; Impaire
      Decalage=1
    Else
      Decalage=-1
    EndIf
    LeChar=PeekA(*Buffer+(x+Decalage)+$D)
    If LeChar=0
      DrapeauFin=1
    EndIf
    If DrapeauFin=0
      LeFichier=LeFichier+Chr(LeChar)
    EndIf
  Next
  ;Debug LeFichier
  ProcedureReturn LeFichier
EndProcedure
Procedure PCRD_ReadWord(Adresse, *Buffer)
  If Int(Mod(Adresse, 2))=1
    MSG_ERREUR("PCRD_ReadWord - Adresse IMPAIRE!")
  EndIf
  
  
  
  
  
EndProcedure


If InitNetwork() = 0
  MessageRequester("Error", "Can't initialize the network !", 0)
  End
EndIf

OpenConsole("VTECH GeniusIQ - PCRamdisk")
EnableGraphicalConsole(1)
PrintN("Console PCRamdisk")
PrintN(" BaseRep:"+Maison$)
PrintN(" -> J'utilise quel port COM ? (tape le chiffre)")
ComPortNumber$=Input()
PortCOM$="COM"+ComPortNumber$
If CreateNetworkServer(2, 6832)


If OpenSerialPort(0, PortCOM$, 500000, #PB_SerialPort_NoParity, 8, 1, #PB_SerialPort_NoHandshake, 16384, 16384)
  PrintN(" Ouverture du port "+PortCOM$+" ok!")
  PrintN(" Attente de 3 sec...")
  ;Delay(3000)
  PrintN(" Passage en mode PCRD...")
  Active_mode_PCRAMDISK()
  While(1)
    If AvailableSerialPortInput(0)
      ReadSerialPortData(0, *Buffy,1)
      Delay(20)
      If PeekA(*Buffy)='I' ; ~~~~ Réception de l'entête uniquement (32 octets)
        ReadSerialPortData(0, *HEADER_buffer,32)
        
        CmdRes=(PeekU(*HEADER_buffer+#FRAM_CMDRES) & $FF)
        
        
        ;MSG_INSTRUCTION("Instruction recu : CMDRES=$"+RSet(Hex(CmdRes), 2, "0"))
        Select CmdRes
          Case 0
            MSG_INSTRUCTION("------------------------------")
            MSG_DEBUG(" -> INIT. du systeme",0)
            MSG_VERT("Ne retourne rien")
            EnvoieJusteHEADER()
          Case 1
            MSG_DEBUG(" -> Version du firmware",1)
            EnvoieJusteHEADER()
          Case 2
            MSG_DEBUG(" -> INIT. de la memoire de stockage",0)
            PokeU(*HEADER_buffer+#FRAM_CMDRES,0) ; INIT Ok
            MSG_VERT("OK!")
            EnvoieJusteHEADER()
          Case 3
            LeFichier$=PCRD_LisFichier(*HEADER_buffer)
            MSG_DEBUG(" -> Ouvre un fichier : "+LeFichier$,0)
            ; TODO : Mode d'ouverture du fichier WORDA
            ModeOuverture=PeekU(*HEADER_buffer+#FRAM_WORDA)
            If ModeOuverture=$42
              status=CreateFile(25, Maison$+LeFichier$)
              MSG_DEBUG(" en ECRITURE ",0)
            Else
              status=ReadFile(25, Maison$+LeFichier$)
              MSG_DEBUG(" en LECTURE ",0)
            EndIf
            If status<>0
              MSG_VERT("OK!")
              PokeU(*HEADER_buffer+#FRAM_CMDRES,0) ; OK
            Else
              MSG_ROUGE("Fichier introuvable")
              PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
            EndIf
            EnvoieJusteHEADER()
          Case 4
            MSG_DEBUG(" -> Ferme un fichier",0)
            MSG_VERT("OK!")
            If IsFile(25)
              CloseFile(25)
            EndIf
            EnvoieJusteHEADER()
          Case 5
            MSG_DEBUG(" -> Lis des donnees du fichier",0)
            If Not IsFile(25)
              MSG_ROUGE("FAIL!")                        
              PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
              EnvoieJusteHEADER()
            Else
              If Lof(25)>4096
                ; MULTIPART FILE
                NbrOctetsLus=ReadData(25, *DATA_buffer, 4096)
              Else
                NbrOctetsLus=ReadData(25, *DATA_buffer, Lof(25))
              EndIf
              MSG_DEBUG(" Len:"+Str(NbrOctetsLus)+" ",0)
              If NbrOctetsLus=0
                PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
                EnvoieJusteHEADER()
                MSG_ROUGE("FAIL!")
              Else
                PokeU(*HEADER_buffer+#FRAM_CMDRES,0) ; Ok...
                PokeU(*HEADER_buffer+#FRAM_WORDB,NbrOctetsLus) 
                PokeA(*Buffy, 'Y')
                WriteSerialPortData(0, *Buffy, 1)
                WriteSerialPortData(0, *HEADER_buffer,32)
                PCRD_UART_to_BUFFER(*DATA_buffer)
                MSG_VERT("OK!")
              EndIf
            EndIf

          Case 6  ; Fonction à double "interruption", voir plus bas dans le code . . . . 
            MSG_DEBUG(" -> Ecris des donnees vers le fichier",1)
            PokeA(*Buffy, 'X')
            EnvoieJusteHEADER()
          Case 7
            MSG_DEBUG(" -> Renvoie la position dans le fichier",0)
            If Not IsFile(25)
              MSG_ROUGE("FAIL! (pas de fichier ouvert)")                        
              PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
              EnvoieJusteHEADER()
            Else
              PokeU(*HEADER_buffer+#FRAM_CMDRES,0) ; Ok...
              ;PokeU(*HEADER_buffer+#FRAM_WORDB,NbrOctetsLus) 
              BUFFER_WriteLong(#FRAM_LONGA, *HEADER_buffer, Loc(25))
              EnvoieJusteHEADER()
              MSG_VERT("OK (Loc:"+Hex(Loc(25))+")")
            EndIf
          Case 8
            MSG_DEBUG(" -> Change la position dans le fichier",0)
            If Not IsFile(25)
              MSG_ROUGE("FAIL! (pas de fichier ouvert)")                        
              PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
              EnvoieJusteHEADER()
            Else
              If BUFFER_ReadLong(#FRAM_LONGA, *HEADER_buffer)>Lof(25) Or BUFFER_ReadLong(#FRAM_LONGA, *HEADER_buffer)<0
                MSG_ROUGE("FAIL! (hors limites)"); (LOC:"+Hex(BUFFER_ReadLong(#FRAM_LONGA, *HEADER_buffer))+") !! (LOF interne:"+Str(Lof(25))+")")                        
                PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
                EnvoieJusteHEADER()
              Else
                PokeU(*HEADER_buffer+#FRAM_CMDRES,0) ; Ok...
                                                     ;PokeU(*HEADER_buffer+#FRAM_WORDB,NbrOctetsLus) 
                MSG_VERT("OK (Loc:"+Hex(BUFFER_ReadLong(#FRAM_LONGA, *HEADER_buffer))+")")
                FileSeek(25, BUFFER_ReadLong(#FRAM_LONGA, *HEADER_buffer))
                EnvoieJusteHEADER()
              EndIf
            EndIf
          Case 9
            MSG_DEBUG(" -> Renvoie la taille du fichier ouvert",1)
            PokeA(*Buffy, 'X')
            WriteSerialPortData(0, *Buffy, 1)
            WriteSerialPortData(0, *HEADER_buffer,32)
          Case $A
            MSG_DEBUG(" -> Supprime un fichier de la memoire",1)
            PokeA(*Buffy, 'X')
            WriteSerialPortData(0, *Buffy, 1)
            WriteSerialPortData(0, *HEADER_buffer,32)
          Case $B
            MSG_DEBUG(" -> Liste les fichiers de la memoire",1)
            PokeA(*Buffy, 'X')
            WriteSerialPortData(0, *Buffy, 1)
            WriteSerialPortData(0, *HEADER_buffer,32)
          Default
            MSG_DEBUG(" -> ???? ENTETE",1)
        EndSelect
      ElseIf PeekA(*Buffy)='D' ; ~~~~ Réception de l'entête + segement HI (32 octets + 4096 octets)
        ReadSerialPortData(0, *HEADER_buffer,32)
        ReadSerialPortData(0, *DATA_buffer,4096)
        
        For x=0 To 2047
          LO=PeekU(*DATA_buffer+x)
          HI=PeekU(*DATA_buffer+x+1)
          
          PokeU(*DATA_buffer+x+1,LO)
          PokeU(*DATA_buffer+x,HI)
          x+1
        Next 
        
        CmdRes=(PeekU(*HEADER_buffer+#FRAM_CMDRES) & $FF)
        
        Select CmdRes
          Case $6
            MSG_DEBUG(" -> Ecris des donnees vers le fichier",0)
            NbrOctetsEnvoyes=PeekU(*HEADER_buffer+#FRAM_WORDA)
            ;PokeU(*HEADER_buffer+#FRAM_WORDA,NbrOctetsEnvoyes)
            If NbrOctetsEnvoyes=0 Or NbrOctetsEnvoyes>4096
              MSG_ERREUR(" ! Pas de donnees envoyes ! ->"+Str(NbrOctetsEnvoyes))
              PokeU(*HEADER_buffer+#FRAM_WORDB,0) ; Rien d'ecris
              PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
              PokeA(*Buffy, 'X')
              WriteSerialPortData(0, *Buffy, 1) ; FAIL
              WriteSerialPortData(0, *HEADER_buffer,32)
            Else
              If Not IsFile(25)
                MSG_ROUGE("FAIL!")                        
                ;PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
                ;PokeA(*Buffy, 'X')
                ;WriteSerialPortData(0, *Buffy, 1)
                ;WriteSerialPortData(0, *HEADER_buffer,32)
                status=0
              Else
                status=WriteData(25, *DATA_buffer, NbrOctetsEnvoyes)
              EndIf
              MSG_DEBUG(" Len:"+Str(NbrOctetsEnvoyes)+" ",0)
              If status=0
                MSG_ERREUR(" Erreur lors de l'ecriture vers le fichier! (PCRD_ERROR)")
                PokeU(*HEADER_buffer+#FRAM_WORDB,0) ; Rien d'ecris
                PokeU(*HEADER_buffer+#FRAM_CMDRES,1) ; FAIL
                PokeA(*Buffy, 'X')
                WriteSerialPortData(0, *Buffy, 1) ; FAIL
                WriteSerialPortData(0, *HEADER_buffer,32)
              Else
                PokeU(*HEADER_buffer+#FRAM_WORDB,NbrOctetsEnvoyes)
                PokeU(*HEADER_buffer+#FRAM_CMDRES,0) ; Ok!
                PokeA(*Buffy, 'X')
                WriteSerialPortData(0, *Buffy, 1) ; Ok!
                WriteSerialPortData(0, *HEADER_buffer,32)
                MSG_VERT("OK!")
              EndIf
            EndIf
          Default
            MSG_DEBUG(" -> ???? ENTETE+DATA",1)
        EndSelect
      Else
        ConsoleColor(15,12)
        PrintN(" Erreur d'interruption! recu:"+Str(PeekA(*Buffy))+" - "+Chr(PeekA(*Buffy))+". Je continue...")
        ConsoleColor(7,0)        
        End
      EndIf
    
    
    EndIf
    Delay(1)
    
    
    ; Reset distant....
    SEvent = NetworkServerEvent()
    If SEvent
      ClientID = EventClient()
      Select SEvent
        Case #PB_NetworkEvent_Connect
          ;MessageRequester("PureBasic - Server", "A new client has connected !", 0)
          MSG_DEBUG("--- Redemarrage distant ---",1)
            If IsFile(25)
              CloseFile(25)
            EndIf
          Active_mode_PCRAMDISK()
        Case #PB_NetworkEvent_Data
        Case #PB_NetworkEvent_Disconnect
      EndSelect
    EndIf

    
    
    
  Wend
  Quitte()
Else
  ConsoleColor(15,12)
  PrintN(" ERREUR lors de l'ouverture du port "+PortCOM$+"!")
  Quitte()
EndIf
Else
  MSG_ERREUR("Impossible de creer le serveur sur le port TCP 6832!")
  Quitte()
EndIf
  
; IDE Options = PureBasic 5.62 (Windows - x86)
; CursorPosition = 510
; FirstLine = 245
; Folding = AAA+
; EnableXP
; Executable = pcrd.exe
; EnablePurifier