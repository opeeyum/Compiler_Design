#List of Keywords
keywords = ["if", "else", "while", "do", "break",
			"continue", "int", "double", "float", 
			"return", "char", "sizeof", "typedef",
			"switch", "void", "static", "struct", "main"]
			

#List of Operators
operators = ['+', '-', '*', '/',
			 '>', '<', '=']

#List of Seprators
seprators = ['+', '-', '*',
			 '/', ',', ';', '>',
			 '<', '=', '(', ')',
			 '[', ']', '{', '}']

# Function to classify the tokens
def identify(st:str):
	if st.isdecimal():
		return "Integer"
	elif st in keywords:
		return "Keyword"
	elif st in operators:
		return "Operator"
	elif st in seprators and st not in operators:
		return "Seprator"
	else:
		return "User defined Identifier"

# Function to print string
def PRINT(st:str):
	global count
	if len(st) != 0:
		result = identify(st)
		print(st, ": ",result)
		count+=1
#------------------------------------------------------------

count = 0 #token count
line = input(">>>> ")
tokens = line.split(' ')
print("\n")

for t in tokens:	
	if len(t) != 1:
		temp = ""
		i = 0; lent = len(t)
		while i < lent:
			if t[i] in seprators:
				PRINT(temp)
				result = identify(t[i])
				print(t[i], ": ",result)
				count+=1
				temp=""

			elif ord(t[i]) == ord("'") :
				i+=1
				f = t[i:].find("'")
				temp += t[i:i+f]
				i+=f
				PRINT(temp)
				temp=""

			elif ord(t[i]) == ord('"'):
				i+=1
				f = t[i:].find('"')
				temp += t[i:i+f]
				i+=f
				PRINT(temp)
				temp=""

			else :
				temp += t[i]
			i+=1

		PRINT(temp)

	else:
		result = identify(t)
		print(t, ": ",result)
		count+=1

print("\nTotal token identified: ",count)



