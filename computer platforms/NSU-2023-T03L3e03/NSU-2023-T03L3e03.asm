	asect	0x00
	# WRITE YOUR CODE HERE




	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
s:		dc _s 	# do NOT use labels _s and _p above!
p:		dc _p	# do NOT use labels _s and _p above!

_s:	dc	"cats like milk",0 # replace that by some string for testing
_p:	dc	"e m",0			   # replace that by some pattern for testing

	ds	40     # reserve more space in case the string from tester is longer than ours
endinputs>
res:	ds	1
	end
