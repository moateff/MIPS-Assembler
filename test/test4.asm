	add $s0, $zero, $zero	# 00008020    
	addi $s0, $zero, 0x78   # 20100078     
	add $s1, $zero, $zero   # 00008820     
	addi $s1, $zero, 0xB4   # 201100b4      
	add $s2, $zero, $zero   # 00009020     
loop:	beq $s0, $s1, end       # 12110006   
	slt $t1, $s0, $s1       # 0211482a      
	beq $t1, $zero, label   # 11200002     
	sub $s1, $s1, $s0       # 02308822  
	j loop                  # 08000005       
label:	sub $s0, $s0, $s1       # 02118022      
	j loop                  # 08000005     
end: 	add $s2, $zero, $s0     # 00109020     
	sw $s2, 0($zero)        # ac120000      
