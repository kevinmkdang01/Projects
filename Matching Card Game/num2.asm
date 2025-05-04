    .data
numbers2: .space 32
    
    .text
    .globl secNum

secNum:
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
    move $s2, $a0
    
randomNum:
    li $a1, 12
    li $v0, 42
    syscall
    
    move $s3, $a0
    addi $s3, $s3, 1
    addi $s4, $0, 0
    
    move $s5, $s2
    add $s5, $s5, $s0
    lb $s5, 0($s5)
    mul $s5, $s5, $s3

checkArray:
    lb $s6, numbers2($s4)
    beq $s6, $s3, randomNum
    
    move $s7, $s2
    add $s7, $s7, $s4
    lb $s7, 0($s7)
    mul $s7, $s6, $s7
    beq $s7, $s5, randomNum

checkNext:
    beq $s4, $s0, addNumber
    addi $s4, $s4, 4
    j checkArray
    
addNumber:
    sb $s3, numbers2($s0)
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
    la $v0, numbers2
    jr $ra
