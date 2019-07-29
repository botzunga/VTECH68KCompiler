fichier$=OpenFileRequester("","","*.*",0)
LeLabel$="tbl_"+LCase(GetFilePart(fichier$,#PB_FileSystem_NoExtension))
compteur=0
*Buf=AllocateMemory(1)
If ReadFile(1,fichier$)
  While(Not Eof(1))
    pile$=""
    For x=0 To 15
      ReadData(1, *Buf, 1)
      If x=0
        pile$=pile$+"$"+RSet(Hex(PeekA(*Buf)), 2, "0")
      Else
        pile$=pile$+", $"+RSet(Hex(PeekA(*Buf)), 2, "0")
      EndIf
      
      
    Next
    Debug LeLabel$+Str(compteur)+Chr(9)+"dc.b"+Chr(9)+" "+pile$
    compteur+1
    
    
    
    
    
    
  Wend
  
  
  
  
EndIf
; IDE Options = PureBasic 5.62 (Windows - x86)
; CursorPosition = 1
; EnableXP