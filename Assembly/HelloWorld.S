; ";" Is to indicate comments
; ".s" files are made for binary files 

; Place directives, to

; Program setup
  AREA prg_1,CODE,READONLY  
			; No
				; Can't edit file once on memory
  ENTRY ; Here on code begins
  
  EXPORT __Temporalmain ; La función main de este archivo, será usada en otro lugar

; Here begins the actual code for main
__Temporalmain;__main 
	MOVS r0, #0x01	; move r0 to mem(0x01)
	ADDS r0, r0, r0 ; r0 = r0+ r0
	END ; Here code ends
		
; We can use a simulator to run the program