    .data
numbers1: .space 32
    
.text
.globl firstNum



firstNum:	
    subi $sp, $sp, 32	
    sw $s0, 28($sp)	
    sw $s1, 24($sp)	
    sw $s2, 20($sp)	
    sw $s3, 16($sp)	
    sw $s4, 12($sp)	
    sw $s5, 8($sp)	
    sw $s6, 4($sp)	
    sw $s7, 0($sp)
    
    addi $s0, $zero, 0	
    addi $s1, $zero, 32	
    
randomNum:	
    li $a1, 12 		
    li $v0, 42		
    syscall
    
    move $s3, $a0	
    addi $s3, $s3, 1	
    addi $s4, $0, 0	

checkArray:	
    lb $s6, numbers1($s4)
    beq $s6, $s3, randomNum 

checkNext:	
    beq $s4, $s0, addNumber 
    addi $s4, $s4, 4	
    j checkArray	

addNumber:	
    sb $s3, numbers1($s0) 
    beq $s0, $s1, done  
    addi $s0, $s0, 4	
    j randomNum		
done: 
    lw $s7, 0($sp)	
    lw $s6, 4($sp)
    lw $s5, 8($sp)
    lw $s4, 12($sp)
    lw $s3, 16($sp)
    lw $s2, 20($sp)
    lw $s1, 24($sp)
    lw $s0, 28($sp)
    addi $sp, $sp, 32	
    la $v0, numbers1	
    jr $ra		