; a tiny example of multi segment executable file.
; data is stored in a separate segment, segment registers must be set correctly.

name "testexe"

data segment PARA 'DATA'
    i dw 0
    j dw 0
    k dw 0
    n dw 0
    flag dw 0
    arr dw 100 dup(0)
    max dw 3003
    dizi dw 3 dup(0)
    YOK db "Verilen dizide ucgen olusturabilecek eleman yok !", 0dh,0ah, '$'    
    message db '(' ,0, ',' ,0, ',' ,0, ')',0dh,0ah, '$'
   ; arr 
    ;msg  db "hello, world!", 0dh,0ah, '$'
data ends

stack segment PARA 'STACK'
    db 30 dup(0)          
    
stack ends

code segment PARA 'CODE'
    ASSUME CS:code,DS:data,SS:stack
   
start PROC FAR           
 
    CALL OKU
    
    IDongu: 
        MOV j,i
        INC j
        
        JDongu:
                  
            MOV k,j
            INC k
                  
            KDongu:
               Call Kontrol
            INC k       
            CMP k,n   
            JZ JDongu    
            JMP KDongu
            
         INC j
         CMP j,n
         JZ IDongu 
         JMP JDongu
     INC i
     CMP i,n
     JNZ IDongu
     
     CALL YAZ   
     
     
     
Kontrol PROC FAR
     XOR EAX,EAX
     XOR EBX,EBX
     XOR ECX,ECX
     MOV EAX, arr[i]
     MOV EBX, arr[j]
     MOV ECX, arr[k]  
     
     ADD eax,ebx
     cmp eax,ecx
     JBE Return
     MOV EAX,arr[i]
     add eax,ecx
     cmp eax,ebx
     JBE Return
     MOV EAX,arr[i]
     ADD ebx,ecx 
     cmp ebx,eax
     JBE Return
     
     ADD ebx,eax      ;ebx=maxA
     CMP max,ebx
     JBE Return
 
     MOV flag,1 
     MOV eax,arr[0]
     MOV dizi[0],eax
     MOV eax,arr[1]
     MOV dizi[1],eax
     MOV eax,arr[2]
     MOV dizi[2],eax
     
    
Return:
RETf    
Kontrol endp

OKU PROC FAR
 PUSH ESI
 MOV ESÝ,0
 ;arr eleman sayisini oku
 XOR AX,AX
 MOV AH,1h
 INT 21H
 MOV n,AL
 Lop:
 
    MOV AH,1h
    INT 21H
    MOV arr[ESI],AL
    ;arr elemanlarini oku
    INC ESI
    CMP ESI,n
    JNE Lop
 
 POP ESI
    
    
RETf  
OKU endp
   
   
   
   
YAZ PROC FAR
   CMP flag,0
   JZ ucgenyok    
   MOV SI,0         
   
   ;messageyi yazdýr
   MOV DL, '('
   MOV AH,2
   INT 21H
   
   MOV DL, dizi[SI]
   INC SI
   INT 21H
   MOV DL,','
   INT 21H
 
   
   MOV DL,dizi[SI]
   INC SI
   INT 21H
   MOV DL,','
   INT 21H
   
   MOV DL,dizi[SI]
   INT 21H
   MOV DL,')'
   INT 21H
   
   RET
ucgenyok:
    ;"Verilen dizide ucgen olusturabilecek eleman yok !"
   lea     dx, YOK
   mov     ah, 09h
   int     21h

    RET


    
    
YAZ endp

end start  ; set entry point and stop the assembler.
        
        
           


