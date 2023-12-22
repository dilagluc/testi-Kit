COL_RED="\033[0;31m"
COL_GRN="\033[0;32m"
COL_END="\033[0m"

UID=$(shell id -u)
GID=$(shell id -g)
VM_DISK_SIZE_MB?=1024

REPO=disk-linux

.PHONY:
ubuntu: ubuntu.img

%.tar:
	@echo ${COL_GRN}"[Dump $* directory structure]"${COL_END}
	docker build -f $*/Dockerfile -t ${REPO}/$* .
	docker export -o $*.tar `docker run -d ${REPO}/$* /bin/true`

# numeric owner to keep owner
%.dir: %.tar
	@echo ${COL_GRN}"[Extract $* tar archive]"${COL_END}
	docker run -it \
		-v `pwd`:/os:rw \
		${REPO}/builder bash -c 'mkdir -p /os/$*.dir && tar -C /os/$*.dir --numeric-owner -xf /os/$*.tar'

%.img: builder %.dir
	@echo ${COL_GRN}"[Create $* disk image]"${COL_END}
	docker run -it \
		-v `pwd`:/os:rw \
		-e DISTR=$* \
		--privileged \
		--cap-add SYS_ADMIN \
		${REPO}/builder bash /os/create_image.sh ${UID} ${GID} ${VM_DISK_SIZE_MB}

.PHONY:
builder:
	@echo ${COL_GRN}"[Ensure builder is ready]"${COL_END}
	@if [ "`docker images -q ${REPO}/builder`" = '' ]; then\
		docker build -f Dockerfile -t ${REPO}/builder .;\
	fi

.PHONY:
clean: clean-docker-procs clean-docker-images
	@echo ${COL_GRN}"[Remove leftovers]"${COL_END}
	rm -rf mnt ubuntu.*

