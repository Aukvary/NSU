	asect 	0x00
	# WRITE YOUR CODE HERE




	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
res:
s:	dc	"...",0 	# replace ... by some text for testing
	ds      17      # reserve more space in case the string from tester is longer than ours
endinputs>
	end
