#Prints out the board
        .data
line: .asciiz "+-------+-------+-------+-------+\n" 
columns: .asciiz "|"				
plus: .asciiz "x"				
hidden1: .asciiz "?"				
new_line: .asciiz "\n"				
space: .asciiz " "
    .text
    .globl board
    
board:		
    subi $sp, $sp, 28	
    sw $ra, 24($sp)
    sw $s0, 20($sp)	
    sw $s1, 16($sp)	
    sw $s2, 12($sp)	
    sw $s3, 8($sp)	
    sw $s4, 4($sp)	
    sw $s5, 0($sp)	
    
    move $s0, $a0	
    move $s1, $a1	
    move $s2, $a2	
    
    addi $t1, $0, 0	
    addi $t2, $0, 4	
    addi $t3, $0, 0	

    
    li $v0, 4		
    la $a0, line
    syscall

printCard:  
    li $v0, 4
    la $a0, columns      
    syscall

    lb $s3, 0($s2)       
    beq $s3, $zero, hiddenCard  
    slti $s4, $s3, 100   
    beq $s4, $zero, printEquation 

    
    sll $s3, $s3, 2       
    subi $s3, $s3, 4     
    
    move $s4, $s0         
    move $s5, $s1         

    add $s4, $s4, $s3     
    add $s5, $s5, $s3    
    lb $s4, 0($s4)        
    lb $s5, 0($s5)        
    mul $s4, $s4, $s5     

    li $s5, 1             
    slti $s3, $s4, 10     
    beq $s3, $s5, oneDigit 
    slti $s3, $s4, 100    
    beq $s3, $s5, twoDigits 

   
    li $a0, 1
    jal printSpace      
    li $v0, 1
    move $a0, $s4          
    syscall
    li $a0, 1
    jal printSpace         
    j next

twoDigits:
    li $a0, 2		 
    jal printSpace	
    li $v0, 1		
    move $a0, $s4	
    syscall
    
    li $a0, 3		
    jal printSpace	
    j next
     
oneDigit:
    li $a0, 3		 
    jal printSpace	
    li $v0, 1		
    move $a0, $s4	
    syscall
    
    li $a0, 3		
    jal printSpace	
    j next		
 
printEquation:
    subi $s3, $s3, 100     
    sll $s3, $s3, 2        
    subi $s3, $s3, 4       
    move $s4, $s0
    move $s5, $s1
    add $s4, $s4, $s3      
    add $s5, $s5, $s3
    lb $s4, 0($s4)
    lb $s5, 0($s5)

    li $v0, 1
    move $a0, $s4          
    syscall
    li $v0, 4
    la $a0, plus          
    syscall
    li $v0, 1
    move $a0, $s5          
    syscall
    li $a0, 1
    jal printSpace         
    j next
    
Ftwo:
    li $a0, 1		
    jal printSpace	
    li $v0, 1		
    move $a0, $s4	
    syscall

nextDig:
    li $v0, 4		
    la $a0, plus	
    syscall
    
    slti $s3, $s5, 10	
    beq  $s3, $0, Stwo	
    
    li $v0, 1		
    move $a0, $s5	
    syscall
    li $a0, 2
    jal printSpace
    j next

Stwo:
    li $v0, 1		
    move $a0, $s5	
    syscall
    li $a0, 1
    jal printSpace
    j next

hiddenCard:		
    li $a0, 3		
    jal printSpace
    li $v0, 4
    la $a0, hidden1	
    syscall
    li $a0, 3
    jal printSpace
    j next		

printSpace: 
    addi $sp, $sp, -4	
    sw   $s5, 0($sp)	
    move $s5, $a0	
    subi $s5, $s5, 1

loopSpace:
    li $v0, 4
    la $a0, space
    syscall
    beq $s5, $0, spaceDone
    subi $s5, $s5, 1	
    j loopSpace

spaceDone:
    lw $s5, 0($sp)	
    addi $sp, $sp, 4	
    jr $ra	

next:
    
    
    addi $s2, $s2, 4	
    addi $t1, $t1, 1    
    beq $t1, $t2, nextRow 
    
    j printCard		
    
nextRow:
    li $v0, 4		
    la $a0, columns
    syscall
    
    li $v0, 4		
    la $a0, new_line
    syscall
    
    li $v0, 4		
    la $a0, line
    syscall
    
    addi $t1, $0, 0     
    addi $t3, $t3, 1	
    beq $t2, $t3, done	
    j printCard		

done:
    lw $s5, 0($sp)	
    lw $s4, 4($sp)
    lw $s3, 8($sp)
    lw $s2, 12($sp)
    lw $s1, 16($sp)
    lw $s0, 20($sp)
    lw $ra, 24($sp)
    addi $sp, $sp, 28	
    jr $ra		