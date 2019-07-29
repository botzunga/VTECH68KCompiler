; BuildeurV2 pour ASM68K
;
;
Procedure AfficheAIDE()
  PrintN("AIDE de Buildeur")
  PrintN("--infile [fichier]     Indique le fichier ASM pour la compilation")
  PrintN("--outfile [fichier]    Indique le fichier BIN de la sortie")
  PrintN("--8to16                Convertis la compilation au format WORD")
  PrintN("--gen-odd-even         Genere un fichier IMPAIRE et PAIRE pour des roms 8 bits")
  PrintN("--oddfile [fichier]    Indique le fichier ODD (impaire)")
  PrintN("--evenfile [fichier]   Indique le fichier EVEN (paire)")
  PrintN("--keep-original        Conserve le fichier binaire juste apres MOT2BIN")
  PrintN("--pcrd-send            Envoie le fichier à la plateforme")
  PrintN("... pour le reste, DIY!")
  End
EndProcedure

Procedure TesteFichier(LeFichier$)
  HANDLERReadfile=ReadFile(#PB_Any, LeFichier$)
  If HANDLERReadfile
    CloseFile(HANDLERReadfile)
    ProcedureReturn 1
  Else
    ProcedureReturn 0
  EndIf
EndProcedure

Procedure PCRD_SendReset()
  ; Renvoie 1 si il y a eu une erreur, 0 sinon.
  Port = 6832
  
  ConnectionID = OpenNetworkConnection("127.0.0.1", Port)
  If ConnectionID
    SendNetworkString(ConnectionID, "Hi", #PB_UTF8)
    CloseNetworkConnection(ConnectionID)
    Delay(300)
    ProcedureReturn 0
  Else
    ProcedureReturn 1
  EndIf
  

EndProcedure

OpenConsole("BuildeurV2")
If InitNetwork() = 0
  PrintN("ERREUR - J'ai besoin d'une pile reseau pour fonctionner correctement.")
  dummy$=Input()
  End
EndIf
cmdline$=LCase(ProgramParameter())

If FindString(cmdline$, "--help") Or FindString(cmdline$, "/?") Or FindString(cmdline$, "/help")
  AfficheAIDE()
EndIf

If CountProgramParameters()<2
  AfficheAIDE()
EndIf

For x=0 To CountProgramParameters()
  _tmp$=LCase(ProgramParameter(x))
  Select _tmp$
    Case "--infile"
      INFile$=ProgramParameter(x+1)
    Case "--outfile"
      OUTFile$=ProgramParameter(x+1)
      DeleteFile(OUTFile$)
    Case "--8to16"
      SWAP8to16=1
      DoSomething=1
    Case "--gen-odd-even"
      GenerateODDEVEN=1
      DoSomething=1
    Case "--oddfile"
      ODDFile$=ProgramParameter(x+1)
      DeleteFile(ODDFile$)
    Case "--evenfile"
      EVENFile$=ProgramParameter(x+1)
      DeleteFile(EVENFile$)
    Case "--keep-original"
      ORIGINALFile$=ProgramParameter(x+1)
      DeleteFile(ORIGINALFile$)
      DoSomething=1
      KeepOriginalFile=1
    Case "--pcrd-send"
      pcrd_send=1
  EndSelect
Next
If DoSomething=0
  PrintN("[!!!] BUILDEUR - Rien a faire!")
  PrintN("")
  AfficheAIDE()
EndIf
If Not TesteFichier(INFile$)
  PrintN("[!!!] BUILDEUR - INFile n'existe pas!")
  PrintN("")  
  End
EndIf

; 1. Ouverture du fichier
If Not ReadFile(1, INFile$)
  PrintN("[!!!] BUILDEUR - INFile est impossible a lire!")
  PrintN("")
  End
EndIf 

PrintN("[???] - INFile LEN : "+Str(Lof(1)))

CloseFile(1)


;Etape 0 : Nettoyage du répertoire de travail
RepertoireDeTravail$=GetCurrentDirectory()
PrintN("[???] - WrkDir "+RepertoireDeTravail$)
LeFichier$=GetFilePart(INFile$, #PB_FileSystem_NoExtension)
LeFichier$=LeFichier$+".HEX" ; Nom recomposé en cas de création réussie
PrintN(" -> Nettoyage du repertoire de travail")
PrintN(" -> Supression de "+LeFichier$)
DeleteFile(RepertoireDeTravail$+"\"+LeFichier$)

;Etape 1 : Compilation du fichier ASM
Compilateur = RunProgram("asm68k.exe", "-nl "+INFile$, RepertoireDeTravail$, #PB_Program_Wait)

;FIXME: Dans tous les cas, il est IMPOSSIBLE de savoir si la compilation a réussi ou échoué.
;FIXME: Pour cela, je dois regarder si le fichier de sortie a correctement été généré.

;Etape 2 : Vérifier que le fichier de sortie existe et si oui, générer un .BIN
ReadFile(1, RepertoireDeTravail$+"\"+LeFichier$)
If Lof(1)<3
  PrintN("[!!!] La compilation a visiblement echouee!")
  PrintN("")
  Delay(2000)
  End
EndIf
If IsFile(1)
  CloseFile(1)
EndIf



; FAIT CHIER
; MOT2BIN ne supporte pas les espaces dans les chemins mênant aux fichier à traiter.
; Par conséquent, je dois changer de contexte....
; EDIT : WTF??? Sur mon PC de bureau, je n'ai pas de problemes....

ProgrammeMOT2BIN$=RepertoireDeTravail$+"\mot2bin.exe"

RunProgram(ProgrammeMOT2BIN$, Chr(34)+RepertoireDeTravail$+"\"+LeFichier$, RepertoireDeTravail$+Chr(34), #PB_Program_Wait)
If Not TesteFichier(RepertoireDeTravail$+"\"+GetFilePart(LeFichier$, #PB_FileSystem_NoExtension)+".BIN")
  PrintN("[!!!] MOT2BIN a echoue! Le programme peut etre manquant!")
  PrintN("")
EndIf

ReadFile(1, RepertoireDeTravail$+"\"+GetFilePart(LeFichier$, #PB_FileSystem_NoExtension)+".BIN")
PrintN(" -> Chargement du binaire compile en memoire...")
*COMPILProgramme=AllocateMemory(Lof(1))
resultat=ReadData(1, *COMPILProgramme, Lof(1))
If resultat<>Lof(1)
  PrintN("[!!!] Impossible de lire correctement le resultat de la compilation!")
  PrintN("")
  End
EndIf
CloseFile(1)

;Trouve l'endroit des donneees en memoire... necessite .ORG correct...
For x=0 To MemorySize(*COMPILProgramme)-1 ; (0->399 donc 400 octets...)
  If MARQUEPointeur=0 And PeekA(*COMPILProgramme+x)<>$FF
    MARQUEPointeur=1 ; On marque l'endroit a traiter
    EndroitDonnees=x
    SegmentMemoireReel=MemorySize(*COMPILProgramme)-EndroitDonnees
    PrintN(" -> J'ai un debut de donnees @ $"+Hex(EndroitDonnees,#PB_Long))
    PrintN(" -> Taille du programme : "+Str(SegmentMemoireReel)+" octets ($"+Hex(SegmentMemoireReel, #PB_Long)+")")
    If Mod(SegmentMemoireReel, 2)=1
      PrintN(" => Le fichier a une taille impaire.")
      SegmentMemoireReel+1
      DemiSegment=SegmentMemoireReel/2
      SegmentMemoireReel-1
    Else
      DemiSegment=SegmentMemoireReel/2
    EndIf
    *MEM_Paire=AllocateMemory(DemiSegment)
    *MEM_IMPaire=AllocateMemory(DemiSegment)
    *MEM_8TO16=AllocateMemory(SegmentMemoireReel)
    *MEM_Original=AllocateMemory(SegmentMemoireReel)
    ;PrintN("DEBUG : Demisegment - "+Str(DemiSegment)
  EndIf
Next

PrintN(" -> Preparation des segmemts memoires...")
CopyMemory(*COMPILProgramme+EndroitDonnees, *MEM_Original, SegmentMemoireReel)

Incr=0
For x=0 To (SegmentMemoireReel-1) Step 2
  PokeA(*MEM_Paire+Incr, PeekA(*COMPILProgramme+EndroitDonnees+x))
  Incr+1
Next
Incr=0
For x=1 To (SegmentMemoireReel-1) Step 2
  PokeA(*MEM_IMPaire+Incr, PeekA(*COMPILProgramme+EndroitDonnees+x))
  Incr+1
Next
Incr=0
For x=0 To (DemiSegment-1)
  PokeA(*MEM_8TO16+Incr, PeekA(*MEM_IMPaire+x)):Incr+1  
  PokeA(*MEM_8TO16+Incr, PeekA(*MEM_Paire+x)):Incr+1
Next 
If SWAP8to16=1
  PrintN(" -> Instruction 8To16 detecte, ecriture vers "+GetFilePart(OUTFile$))
  If CreateFile(1, OUTFile$)
    WriteData(1, *MEM_8TO16, SegmentMemoireReel)
    CloseFile(1)
  Else
    PrintN("[!!!] Erreur d'ecriture 8to16 vers "+OUTFile$)
    End
  EndIf 
  PrintN(" -> 8To16 OK.")
EndIf
If GenerateODDEVEN=1
  PrintN(" -> GenerateOddEven detecte, je fait ;")
  PrintN("ODD:"+GetFilePart(ODDFile$))
  PrintN("EVEN:"+GetFilePart(EVENFile$))
  
  If CreateFile(1, ODDFile$)
    WriteData(1, *MEM_IMPaire, DemiSegment)
    CloseFile(1)
  Else
    PrintN("[!!!] Erreur d'ecriture ODD vers "+ODDFile$)
    End
  EndIf
  If CreateFile(1, EVENFile$)
    WriteData(1, *MEM_Paire, DemiSegment)
    CloseFile(1)
  Else
    PrintN("[!!!] Erreur d'ecriture EVEN vers "+EVENFile$)
    End
  EndIf
  PrintN(" -> ODD+EVEN OK.")
EndIf
If KeepOriginalFile=1
  PrintN(" -> Je garde l'ancien fichier, je le copie dans "+GetFilePart(ORIGINALFile$))
  CreateFile(1, ORIGINALFile$)
  WriteData(1, *MEM_Original, MemorySize(*MEM_Original))
  CloseFile(1)
EndIf
If pcrd_send=1
  PrintN(" -> --pcrd-send detecte, je vais l'envoyer sur la plateforme...")
  ;OUTFile$
  status=PCRD_SendReset()
  If status=1
    LeFichier$=GetFilePart(OUTFile$)
    DeleteFile(GetCurrentDirectory()+"DISK\"+LeFichier$,#PB_FileSystem_Force)
    CopyFile(OUTFile$, GetCurrentDirectory()+"DISK\"+LeFichier$)
    ; Normalement on est bon!
    PrintN(" -> Ok. Fichier envoye")
    
    ; Resident PCRD non lancée, on l'execute...
    RunProgram("pcrd.exe","",GetCurrentDirectory())
    Delay(4000) ; Attente que PCRD soit prêt...
    
    status=PCRD_SendReset()
    If status=1
      PrintN("!!! Erreur d'execution de PCRD! Verifie si tout vas bien...")
      End
    EndIf
  Else
    LeFichier$=GetFilePart(OUTFile$)
    DeleteFile(GetCurrentDirectory()+"DISK\"+LeFichier$,#PB_FileSystem_Force)
    CopyFile(OUTFile$, GetCurrentDirectory()+"DISK\"+LeFichier$)
    PrintN(" -> Ok. Fichier envoye")
  EndIf
EndIf
PrintN(" -> Buildeur a fini. Merci!")
End



 








  
  
  
  
  
  
  
  

; IDE Options = PureBasic 5.62 (Windows - x86)
; ExecutableFormat = Console
; CursorPosition = 255
; FirstLine = 208
; Folding = 6
; EnableXP
; Executable = buildeurv2.exe