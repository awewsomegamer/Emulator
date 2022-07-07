#include <error_handler.h>

void m_printf(char* message, va_list args){
	int message_i = 0;

	char* s;
	int v;
	bool arg_found = false;

	while (*(message + message_i)){
		char c = *(message + message_i);

		if (c == '%'){
			switch (*(message + message_i + 1)){
			case 's':
				s = va_arg(args, char*);
				printf("%s", s);

				message_i++;
				arg_found = true;

				break;

			case 'd':
				v = va_arg(args, int);
				printf("%d", v);

				message_i++;
				arg_found = true;

				break;

			case 'c':
				v = va_arg(args, char);
				printf("%c", v);

				message_i++;
				arg_found = true;

				break;

			case 'X':
				v = va_arg(args, int);
				printf("%X", v);

				message_i++;
				arg_found = true;

				break;
			}
		}

		if (!arg_found)
			printf("%c", c);
		
		message_i++;
		arg_found = false;
	}
}

void e_fatal(char* message, char* file, int line, ...){
	va_list args;
	va_start(args, line);

	printf("[FATAL]: In file \"%s\" on line %d.\nMessage: ");
	m_printf(message, args);
	printf("\n");

	exit(1);
}

void e_error(char* message, char* file, int line, ...){
	va_list args;
	va_start(args, line);

	printf("[ERROR]: In file \"%s\" on line %d.\nMessage: ");
	m_printf(message, args);
	printf("\n");
}
