	asect 	0x00
	# WRITE YOUR CODE HERE




	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
array:	dc	 5,-1,-3,7,4,2,2,-8 # choose some numbers for testing
endinputs>
res:	ds	8
	end
