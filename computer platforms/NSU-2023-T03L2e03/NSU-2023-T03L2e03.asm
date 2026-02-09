	asect 	0x00
	# WRITE YOUR CODE HERE





	# at this point 'res' has the answer
	ldi   r0,res
	halt
res:	ds	9	# pointers to at most 8 words and the null
inputs>
s:	dc	"...",0 # replace ... by some text for testing
	ds      57      # reserve more space in case the string from tester is longer than ours
endinputs>
	end
