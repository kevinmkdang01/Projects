    .data
prompt: .asciiz " Select your card (enter a number 1-16): "
error: .asciiz "That tile does not exist. Enter number 1-16.\n"
duplicateMsg: .asciiz "Please select a different card.\n"
new_line: .asciiz "\n"
    .text
    .globl input
    
input:		
    subi $sp, $sp, 28	
    sw $s0, 24($sp)	
    sw $s1, 20($sp)
    sw $s2, 16($sp)
    sw $s3, 12($sp)
    sw $s4, 8($sp)
    sw $s5, 4($sp)
    sw $s6, 0($sp)
   
    move $s6, $a0	
    add $s2, $0, $a1	
    
getCard:	
    add $s5, $0, $0	
    move $s3, $s6	
    
    li $v0, 4		
    la $a0, prompt	
    syscall
    
    li $v0, 5		
    syscall
    move $s0, $v0	
    
    slti $s1, $s0, 17     
    beq $s1, $0, invalid  
    slti $s1, $s0, 1      
    bne $s1, $0, invalid  

verifyGuess:	
    lw $s4, 0($s3)	
    beq $s4, $s0, duplicate	
    bne $s5, $s2, verifyNext	
    j valid

verifyNext:
    addi $s3, $s3, 4	
    addi $s5, $s5, 4	
    j verifyGuess

invalid:
    li $v0, 4		
    la $a0, error	
    syscall
    j getCard		
    
duplicate:
    li $v0, 4		
    la $a0, duplicateMsg
    syscall
    j getCard		

valid:
    move $v0, $s0	
    lw $s6, 0($sp)	
    lw $s5, 4($sp)	
    lw $s4, 8($sp)
    lw $s3, 12($sp)
    lw $s2, 16($sp)
    lw $s1, 20($sp)
    lw $s0, 24($sp)

    addi $sp, $sp, 28

    jr $ra		
