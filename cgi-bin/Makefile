target1=./login/login.cgi
target2=./singup/singup.cgi
target3=./find/find.cgi
target4=./write_off/write_off.cgi
target5=./change_password/change_password.cgi
target6=./getuser/getuser.cgi
target7=./find_account/find_account.cgi
target8=./set_key/set_key.cgi
target9=./modifying_user_rights/modifying_user_rights.cgi
target10=./top_up/top_up.cgi
target11=./get_card/get_card.cgi
target12=./deduction_of_fee/deduction_of_fee.cgi
FLAGS = -Wall
CC = gcc
all:$(target1) $(target2) $(target3) $(target4) $(target5) $(target6) $(target7) $(target8) $(target9) $(target10) $(target11) $(target12)
$(target1):./login/login.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target2):./singup/singup.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target3):./find/find.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target4):./write_off/write_off.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target5):./change_password/change_password.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target6):./getuser/getuser.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target7):./find_account/find_account.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target8):./set_key/set_key.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target9):./modifying_user_rights/modifying_user_rights.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target10):./top_up/top_up.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target11):./get_card/get_card.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
$(target12):./deduction_of_fee/deduction_of_fee.o sqlite3.o
	$(CC) $^ -o $@ $(FLAGS) -lpthread -ldl
%.o:%.c
	$(CC) -c $^ -o $@ $(FLAGS)
.PHONY:clean
clean:
	rm example ./login/*.o -rfv	
	rm example ./singup/*.o -rfv
	rm example ./find/*.o -rfv
	rm example ./write_off/*.o -rfv
	rm example ./change_password/*.o -rfv
	rm example ./getuser/*.o -rfv
	rm example ./find_account/*.o -rfv
	rm example ./set_key/*.o -rfv
	rm example ./modifying_user_rights/*.o -rfv
	rm example ./top_up/*.o -rfv
	rm example ./get_card/*.o -rfv
	rm example ./deduction_of_fee/*.o -rfv