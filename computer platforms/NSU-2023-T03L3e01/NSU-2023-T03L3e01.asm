	asect	0x00
	# WRITE YOUR CODE HERE




        # at this point 'result' has the answer
        ldi   r0,result
        halt
inputs>
S:	dc	"{f,a,z,q}",0 	# replace by your choice of S for testing
	ds	40	# reserve more space in case the string from tester is longer than ours
endinputs>
result: ds	4
        end
