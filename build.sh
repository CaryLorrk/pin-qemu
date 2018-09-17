ROOT=/local/carywu/pin/pin-qemu

usage() {
    echo "Usage: build.sh [Options] Operation..."
    echo
    echo "Options:"
    echo "-h        Print this message"
    echo "-d        Set DIR [test]"
    echo "-c        \"QEMU config options\""
    echo "-g        Guest ISA [arm]"
    echo "-m        Mode [linux-user]"
    echo "-t        pintool [inscount0.so]"
    echo
    echo "Operations:"
    echo "clean     Clean DIR. If DIR=all, clean all."
    echo "build     Configure, make, and install."
    echo "make      Make and install."
    echo "test      Test with a samll program."
    echo "remove    Remove unused file."
    echo "recover   Recover unused file."
    echo "debug     debug tcg and output to debug.log"
}

while getopts ":c:d:g:m:p:h" opt; do
    case $opt in
        h)
            usage
            exit 0
            ;;
        c)
            CONFIG_OPTIONS=$OPTARG
            ;;
        d)
            DIR=$OPTARG
            ;;
        g)
            GUEST=$OPTARG
            ;;
        m)
            MODE=$OPTARG
            ;;
        t)
            OPTIONS=$OPTARG
            ;;
        t)
            PINTOOL=$OPTARG
            ;;
        \?)
            echo "Invalid option: -$OPTARG"
            usage
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument."
            exit 1
            ;;
    esac
done


SRC=$ROOT/src
TEMP=$ROOT/temp/${DIR-"test"}
BUILD=$ROOT/build/${DIR-"test"}
TEST=$ROOT/linux-user-test-0.3
TARGET_LIST="${GUEST="arm"}-${MODE="linux-user"}"
PINTOOL=${PINTOOL-"pintool/inscount0/inscount0.so"}

shift $(($OPTIND -1))

echo_and_run() { echo "build.sh: $@"; "$@"; }

if [ -z $@ ]; then
    usage
fi

for op in $@; do
    case $op in
        remove)
            for i in `cat $ROOT/unused`; do
                mkdir -p backup/$i
                echo_and_run mv $ROOT/src/$i/* $ROOT/backup/$i
            done
            ;;
        recover)
            for i in `cat $ROOT/unused`; do
                echo_and_run mv $ROOT/backup/$i/* $ROOT/src/$i
            done
            ;;
        clean)
            if [ "$DIR" == "all" ]; then
                echo_and_run rm -rf temp
                echo_and_run rm -rf build
            else
                echo_and_run rm -rf $TEMP
                echo_and_run rm -rf $BUILD
            fi
            ;;
        build)
            echo_and_run rm -rf $TEMP
            echo_and_run rm -rf $BUILD
            echo_and_run mkdir -p $TEMP
            echo_and_run mkdir -p $BUILD
            echo_and_run cd $TEMP;
            echo_and_run $SRC/configure --prefix=$BUILD \
                --target-list=$TARGET_LIST \
                --disable-pie \
                --enable-debug \
                --enable-pin \
                $CONFIG_OPTIONS \
                && make -j8 install
            ;;

        make)
            if [ ! -d $TEMP ]; then
                echo "Cannot find ${TEMP}. Use build to configure and make"
                exit 1;
            fi
            if [ ! -d $BUILD ]; then
                echo_and_run mkdir -p $BUILD
            fi
            echo_and_run cd $TEMP;
            echo_and_run make -j8 install
            ;;

        test)
            if [ ! -x $BUILD/bin/qemu-$GUEST ]; then
                echo "Cannot find qemu-${GUEST}. Use build to configure and make"
                exit 1;
            fi
            echo_and_run $BUILD/bin/qemu-$GUEST -t ${PINTOOL}  -L $TEST/gnemul/qemu-$GUEST $TEST/$GUEST/ls
            ;;
        debug)
            if [ ! -x $BUILD/bin/qemu-$GUEST ]; then
                echo "Cannot find qemu-${GUEST}. Use build to configure and make"
                exit 1;
            fi
            echo_and_run $BUILD/bin/qemu-$GUEST -t ${PINTOOL} -d in_asm,op,out_asm -D debug.log -L $TEST/gnemul/qemu-$GUEST $TEST/$GUEST/ls
            ;;
        *)
            echo "iNVAlid option: $op"
            usage
            exit 1
            ;;
    esac
done
