  PUBLIC EightBitHistogram
  SECTION .text: CODE
  THUMB
  
ResetArray
  STR R7, [R3], #2
  ADD R6, #1
  CMP R6, #256
  
  BNE ResetArray
  BX LR

GenerateHistogram
  MOV R3, R5
  LDRB R7, [R2], #1
  ADD R7, R7
  
  LDR R8, [R3, R7]
  ADD R8, #1
  ADD R3, R7
  STR R8, [R3]
  
  ADD R6, #1
  CMP R6, R4
  
  BNE GenerateHistogram
  BX LR
 
EightBitHistogram
    MUL R4, R0, R1 
    MOV R5, R3
    
    CMP R4, #65536
    ITT GT
      MOVGT R0, #0
      BXGT LR
      
    MOV R6, #0
    MOV R7, #0
    PUSH {LR}
    BL ResetArray
    POP {LR}
    
    MOV R6, #0
    PUSH {LR}
    BL GenerateHistogram
    POP {LR}
    
    MOV R0, R4
      
    BX LR
	
  END