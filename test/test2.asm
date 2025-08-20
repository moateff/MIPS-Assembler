	add $s0, $zero, $zero       # 00008020       
	addi $s0, $zero, 0x07       # 20100007       
	add $s1, $zero, $zero       # 00008820      
	addi $s1, $zero, 0x01       # 20110001  
label: 	beq $s0, $zero, end         # 12000003      
	mul $s1, $s1, $s0           # 02308818       
	addi $s0, $s0, -1           # 2210ffff   
	j label                     # 08000004  
end: 	sw $s1, 0($zero)            # ac110000  
