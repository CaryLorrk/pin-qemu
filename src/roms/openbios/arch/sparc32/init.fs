:noname
  ."   Type 'help' for detailed information" cr
  \ ."   boot secondary slave cdrom: " cr
  \ ."    0 >  boot hd:2,\boot\vmlinuz root=/dev/hda2" cr
  ; DIAG-initializer

: make-openable ( path )
  find-dev if
    begin ?dup while
      \ install trivial open and close methods
      dup active-package! is-open
      parent
    repeat
  then
;

: preopen ( chosen-str node-path )
  2dup make-openable

  " /chosen" find-device
  open-dev ?dup if
    encode-int 2swap property
  else
    2drop
  then
;

:noname
  set-defaults
; PREPOST-initializer

\ preopen device nodes (and store the ihandles under /chosen)
:noname
  " memory" " /memory" preopen
  " mmu" " /virtual-memory" preopen
; SYSTEM-initializer

device-end

: rmap@    ( virt -- rmentry )
  drop 0
  ;

\ D5.3 SBus specific on-board memory address space
: obmem ( -- space )
  0
  ;

\ Load TCX FCode driver blob
[IFDEF] CONFIG_DRIVER_SBUS
  -1 value tcx-driver-fcode
  " QEMU,tcx.bin" $encode-file to tcx-driver-fcode
[THEN]
