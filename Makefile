#!/bin/bash

all: configure

configure: 
	@cd Data ; \
		for dir in `ls`;do \
		cp ../subq.con $${dir} ;\
		echo $${dir}' generating' ;\
		cd $${dir} ;\
		awk  '{if($$3=="run.sh") $$3="Data/""'$${dir}/$${dir}.csh'"""; print > "subq.con"}' subq.con ; \
		awk  '{if($$3=="job.log") $$3="Data/""'$${dir}'""/job.log"; print > "subq.con"}' subq.con ; \
		awk  '{if($$3=="job.out") $$3="Data/""'$${dir}'""/job.out"; print > "subq.con"}' subq.con ; \
		awk  '{if($$3=="job.err") $$3="Data/""'$${dir}'""/job.err"; print > "subq.con"}' subq.con ; \
		cd .. ;\
		echo "#!/bin/csh" > $${dir}/$${dir}.csh ;\
		echo "root4star -q -b -l 'readPicoDst.C(\"Data/$${dir}/file.list\",\"Data/$${dir}/auau27.root\")'" >> $${dir}/$${dir}.csh;\
		chmod 755 $${dir}/$${dir}.csh ;\
	done ; \

submit:
	@for dir in `ls Data` ; do \
		condor_submit Data/$${dir}/subq.con; \
	done 

check:
	@cd Data ; \
	for dir in `ls` ; do \
		if [ -e "$${dir}/tmpl.pid" ];then \
			exitcode=`cat $${dir}/tmpl.pid` ; \
			echo "$${dir}'s exitcode is $${exitcode}." ; \
			if [ $${exitcode} -ne 0 ]; then \
				echo "job failed" ; \
			else \
				echo "job succeeded" ; \
			fi; \
		else \
			echo "$${dir} not finished" ; \
		fi ; \
	done

clean:
	for dir in `ls Data`;do \
		rm Data/$${dir}/job.out; \
		rm Data/$${dir}/job.err; \
		rm Data/$${dir}/job.log; \
        rm Data/$${dir}/auau27.root;\
	done

clearRoot:
	for dir in `ls Data`;do \
		rm Data/$${dir}/auau27.root ; \
	done
	
merge:
	@cdir=`pwd` ; \
	mkdir _merge ; \
	cd Data/TASK1 ; \
	rootfiles=(`find * -name '*.root'`) ; \
	cd $${cdir}/Data ; \
	for file in $${rootfiles[@]}; do \
		roots=() ; \
		for dir in `ls`; do \
			if [ -d $${dir} ];then \
				roots=($${roots[@]} $${dir}/$${file}) ; \
			fi ; \
		done ; \
		echo hadd ../_merge/$${file} $${roots[@]} ; \
		hadd ../_merge/$${file} $${roots[@]} ; \
	done

chec:
	@for dir in `ls Data` ;do\
		ls -hl Data/$${dir}/*.root ;\
	done

mer:
	hadd auau54_merged.root `find Data -name '*.root'`

clearEmpty:
	find Data -name "*" -type f -size 0c | xargs -n 1 rm -f

submitEmpty:
	for dir in `ls Data` ;do\
		if [ ! -f Data/$${dir}/AuAu54.root ];then \
			condor_submit Data/$${dir}/subq.con ;\
		fi ; \
	done
