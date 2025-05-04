#
        .data
new_line: .asciiz "\n"
values: .space 64
    .text
    .globl type
    
type:
    subi $sp, $sp, 28
    sw $s0, 24($sp)
    sw $s1, 20($sp)
    sw $s2, 16($sp)
    sw $s3, 12($sp)
    sw $s4, 8($sp)
    sw $s5, 4($sp)
    sw $s6, 0($sp)
    
    addi $s0, $zero, 0
    addi $s3, $zero, 64

createType:
    li $a1, 2
    li $v0, 42
    syscall
    move $s6, $a0
    
createNum:
    li $a1, 8
    li $v0, 42
    syscall
    
    move $s1, $a0
    addi $s1, $s1, 1
    addi $s4, $0, 0
    beq $s6, $0, check
    addi $s1, $s1, 100
check:
    lb $s5, values($s4)
    beq $s5, $s1, createType
    bne $s4, $s0, checkNext
    j addNum
    
checkNext:
    addi $s4, $s4, 4
    j check
 
addNum:
    sb $s1, values($s0)
    addi $s0, $s0, 4
    beq $s0, $s3, done
    j createType

done:
    lw $s6, 0($sp)
    lw $s5, 4($sp)
    lw $s4, 8($sp)
    lw $s3, 12($sp)
    lw $s2, 16($sp)
    lw $s1, 20($sp)
    lw $s0, 24($sp)
    addi $sp, $sp, 28
    la $v0, values
    jr $ra
