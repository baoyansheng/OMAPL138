################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main_ds1687.obj: ../main_ds1687.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="D:/ti/controlSUITE/device_support/f28m35x/v205/MWare" --include_path="D:/ti/controlSUITE/device_support/f28m35x/v205/MWare" --gcc --define=ccs --diag_warning=225 --display_error_number --diag_wrap=off --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="main_ds1687.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="D:/ti/controlSUITE/device_support/f28m35x/v205/MWare" --include_path="D:/ti/controlSUITE/device_support/f28m35x/v205/MWare" --gcc --define=ccs --diag_warning=225 --display_error_number --diag_wrap=off --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


