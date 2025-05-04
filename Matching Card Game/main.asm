    .data
welcome: .asciiz "Let's play a matching game!\n"
match: .asciiz "You got a match!\n"
nomatch: .asciiz "Try again!\n"
ending: .asciiz "You won!! All cards have been matched! \n" 	 
guess: .space 32						 
cards: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	 
selections: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
    .text
    .globl main

main:
    add $a0, $0, $0	
    jal firstNum		
    move $s0, $v0	

    move $a0, $s0	
    jal secNum		
    move $s1, $v0	

    jal type		
    move $s2, $v0	

    move $a0, $s0	
    move $a1, $s1
    move $a2, $s2

    addi $t3, $0, 64	
    addi $s3, $0, 0	

    li $v0, 4			
    la $a0, welcome		
    syscall

game_loop:
    la $t0, cards	
    la $t1, selections	

    move $a0, $s0	
    move $a1, $s1	
    move $a2, $t0	

    sub $sp, $sp, 12	
    sw $t1, 8($sp)	
    sw $t2, 4($sp)
    sw $t3, 0($sp)
    jal board		
    jal delay	

    lw $t3, 0($sp)	
    lw $t2, 4($sp)
    lw $t1, 8($sp)
    addi $sp, $sp, 12

    la $t0, selections	
    move $a0, $t0	
    li $a1, 64		
    jal input		
    move $s4, $v0	
    add $t0, $t0, $s3	
    sb $s4, 0($t0)	
    addi $s3, $s3, 4	

    la $t0, cards	
    subi $s4, $s4, 1	
    sll $s4, $s4, 2	
    move $t4, $s4	
    add $t0, $t0, $s4	
    add $s4, $s4, $s2	
    lb $s4, 0($s4)	
    sb $s4, 0($t0)	

    la $t0, cards	
    move $a0, $s0	
    move $a1, $s1	
    move $a2, $t0	

    subi $sp, $sp, 12	
    sw $t1, 8($sp)	
    sw $t2, 4($sp)
    sw $t3, 0($sp)
    jal board		
    jal delay		

    lw $t3, 0($sp)	
    lw $t2, 4($sp)
    lw $t1, 8($sp)
    addi $sp, $sp, 12	
    la $t1, selections	

    move $a0, $t1	
    li $a1, 64		
    jal input		
    move $s5, $v0	
    add $t1, $t1, $s3	
    sb $s5, 0($t1)	
    addi $s3, $s3, 4

    la $t1, cards
    subi $s5, $s5, 1	
    sll $s5, $s5, 2	
    move $t5, $s5	
    add $t1, $t1, $s5	
    add $s5, $s5, $s2	
    lb $s5, 0($s5)	
    sb $s5, 0($t1)	

    la $t1, cards
    move $a0, $s0	
    move $a1, $s1	
    move $a2, $t1	

    sub $sp, $sp, 12	
    sw $t1, 8($sp)	
    sw $t2, 4($sp)
    sw $t3, 0($sp)
    jal board
    jal delay

    lw $t3, 0($sp)	
    lw $t2, 4($sp)
    lw $t1, 8($sp)
    addi $sp, $sp, 12

check_match:
   slti $s6, $s4, 100		
   beq $s6, $0, Fguess		
   j nextSel			

Fguess:
    subi $s4, $s4, 100		

nextSel:
    slti $s6, $s5, 100		
    beq $s6, $0, Sguess		
    j check_win			

Sguess:
    subi $s5, $s5, 100		

check_win:
    beq $s4, $s5, correct	
    j incorrect			

correct: 
    li $v0, 4			
    la $a0, match		
    syscall			
    jal delay			

    li $v0, 42
    syscall
    beq $t3, $s3, done
    j game_loop			

incorrect:
    li $v0, 4			
    la $a0, nomatch		
    syscall
    jal delay		

    addi $s4, $0, 0		
    la $t0, cards		
    la $t1, cards		
    add $t0, $t0, $t4		
    add $t1, $t1, $t5		

    sb $s4, 0($t0)		
    sb $s4, 0($t1)		

    la $t0, selections	
    add $t0, $t0, $t3	
    subi $t0, $t0, 4		
    sw $zero, 0($t0)	
    subi $t0, $t0, 4		
    sw $zero, 0($t0)	
    subi $s3, $s3, 8		

    j game_loop			

done:
    li $v0, 4			
    la $a0, ending		
    syscall
    
    li $v0, 10			
    syscall

delay:
    li $t0, 500000		
loop:
    subi $t0, $t0, 1		
    bnez $t0, loop		
    jr $ra			
