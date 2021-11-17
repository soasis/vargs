.code

__ztdc_vcxx_x64_read_homed_register_rcx proc
	mov rax, QWORD PTR [rcx+8]
	ret 0
__ztdc_vcxx_x64_read_homed_register_rcx endp

__ztdc_vcxx_x64_read_homed_register_rdx proc
	mov rax, QWORD PTR [rcx+16]
	ret 0
__ztdc_vcxx_x64_read_homed_register_rdx endp

__ztdc_vcxx_x64_read_homed_register_r8 proc
	mov rax, QWORD PTR [rcx+24]
	ret 0
__ztdc_vcxx_x64_read_homed_register_r8 endp

__ztdc_vcxx_x64_read_homed_register_r9 proc
	mov rax, QWORD PTR [rcx+32]
	ret 0
__ztdc_vcxx_x64_read_homed_register_r9 endp

__ztdc_vcxx_x64_read_register_xmm0 proc
	ret 0
__ztdc_vcxx_x64_read_register_xmm0 endp

__ztdc_vcxx_x64_read_register_xmm1 proc
	movaps xmm0, xmm1
	ret 0
__ztdc_vcxx_x64_read_register_xmm1 endp

__ztdc_vcxx_x64_read_register_xmm2 proc
	movaps xmm0, xmm2
	ret 0
__ztdc_vcxx_x64_read_register_xmm2 endp

__ztdc_vcxx_x64_read_register_xmm3 proc
	movaps xmm0, xmm3
	ret 0
__ztdc_vcxx_x64_read_register_xmm3 endp

END
