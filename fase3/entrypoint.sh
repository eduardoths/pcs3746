#!/bin/bash
set -e

if [[ "$*" ]] ; then
    su student -c "env PATH=$PATH $*"
else
    su - student
fi
