	asect	0x00
	# WRITE YOUR CODE HERE




	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
n:	dc	0 		# replace 0 by your choice of n for testing
s:	dc	"...",0 	# replace ... by some text for testing
	ds	18 	# reserve more space in case the string from tester is longer than ours
endinputs>
res:	ds	1
	end
