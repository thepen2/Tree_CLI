# Tree_CLI<br><br>

The /bin directory contains Nano S compiles and our tree_cli.exe command line program to test the new functions, for the Tree crytpocurrency application interface.<br><br>

CHANGES TO THE FOLLOWING FILES:<br>
/src/common/base58.c (new functions to verify base58 and decimal char arrays)<br>
/src/common/base58.h<br>
/src/handler/sign_tx.c (forks to new transaction format handlers)<br>
/src/transaction/deserialize.c (new functions to parse additional transaction formats)<br>
/src/transaction/deserialize.h<br>
/src/transaction/types.h (new transaction struct elements and additional error messsage defines)<br>
/src/ui/display.c (handlers for the new transaction signing operations)<br>
/src/ui/display.h<br>
/src/ui/menu.c (added UX functions to display two account type public keys)<br>
/src/ui/menu.h<br>
ALL CHANGES CAN BE FOUND BY SEARCHING THE ABOVE FOR "PEN:"<br><br>

ALSO ADDED ICONS:<br>
/icons/nanos_app_tree4.gif<br>
/icons/nanox_app_tree4.gif<br>
/glyphs/boilerplate_logo.gif (overwritten)<br>
Makefile (uploaded here also) modified to reflect icon name changes.<br><br>

Copy the above named files to the existing app-boilerplate repo to duplicate our build.<br><br>


