package hr.fer.oprpp1.hw02.prob1;


/**
 * @author Dominik
 * Implements "lazy" lexer with two states, BASIC and EXTENDED. Token types: NUMBER, WORD, SYMBOL and EOF
 */
public class Lexer {
	
	/**
	 * input text
	 */
	private char[] data;
	/**
	 * current token (last generated)
	 */
	private Token token;
	/**
	 * index of char to analyze
	 */
	private int currentIndex; 
	/**
	 *  state of Lexer, BASIC or EXTENDDED
	 */
	private LexerState state; 
	
	
	/**
	 * @param text Input to be tokenized
	 */
	public Lexer(String text) {
		if(text == null) throw new NullPointerException("Can't pass null!");
		this.data = text.toCharArray();
		this.currentIndex = 0;
		this.state = LexerState.BASIC;
	}
	
	/**
	 * Setter method, changes state of lexer
	 * @param state State to put lexer in
	 */
	public void setState(LexerState state) {
		if (state == null) throw new NullPointerException("Can't pass null!");
		this.state = state;
	}

	
	/**
	 * Generates and returns token, internally delegates "real work" to other private methods
	 * @return token
	 */
	public Token nextToken() {
		if(state == LexerState.EXTENDED) {
			return nextTokenExtended();
		}
		return nextTokenBasic();
	}
	
	/**
	 * Generates and returns token while in basic mode
	 * @return token
	 */
	private Token nextTokenBasic() {
		if (token != null && token.getType() == TokenType.EOF  ) { //check for null because of initial null reference
            throw new LexerException("It's illegal to create token after EOF token.");
        }

        

        String s = "";
        TokenType currType = TokenType.EOF;
	
        skipBlanks();
        
        while (true) {
            if (currentIndex >= data.length) {
                break;
            }
            
            if (Character.isDigit(data[currentIndex])) {
                if (currType == TokenType.EOF) currType = TokenType.NUMBER;
                else if (currType != TokenType.NUMBER) break;
                s += String.valueOf(data[currentIndex++]);

            }
            else if (Character.isLetter(data[currentIndex])) {
                if (currType == TokenType.EOF)  currType = TokenType.WORD; 
                else if (currType != TokenType.WORD)  break;
                s += String.valueOf(data[currentIndex++]);

            } 
            else if (data[currentIndex] == '\\') {
            	if (currType == TokenType.EOF)  currType = TokenType.WORD;
                else if (currType != TokenType.WORD) break;
                
                currentIndex++;
                
                if (currentIndex >= data.length) throw new LexerException("Can't generate token, out of range!");
  
                if (data[currentIndex] == '\\' || Character.isDigit(data[currentIndex])) s += String.valueOf(data[currentIndex++]);
                else throw new LexerException("After escaping, letter is illegal");
                

            }
            else if (data[currentIndex]!=' ' && data[currentIndex]!='\t' && data[currentIndex]!='\r' && data[currentIndex]!='\n') {
                
                if (currType == TokenType.EOF) {
                    currType = TokenType.SYMBOL;
                    s += String.valueOf(data[currentIndex++]);
                } 
                else {
                    break;
                }
            } 
            else {
                break;
            }
        }

        //Generate tokens depending on what is decided above
        if (currType == TokenType.WORD)
        	token = new Token(currType, s);
        else if (currType == TokenType.NUMBER) {
        	try {
        		long result = Long.parseLong(s);
        		token = new Token(currType, result);
        	}
        	catch (NumberFormatException e) {
				throw new LexerException("Cannot parse to long, number is not in correct format!");
			}
        }
        
        else if (currType == TokenType.SYMBOL) {
        		token = new Token(currType, s.charAt(0));
        	
        }	
        else if (currType == TokenType.EOF) {
        	token = new Token(currType, null);
        }

        return token; //returns to function nextToken();
	}
	
	/** Generates and returns token while in extended mode
	 * @return token
	 */
	public Token nextTokenExtended() {
		if (token != null && token.getType() == TokenType.EOF) {
            throw new LexerException("It's illegal to create token after EOF token.");
        }
		
		String s = "";
		skipBlanks();
		
		while (true) {
			
			if(currentIndex >= data.length) break;
			if(data[currentIndex] == '#'  || data[currentIndex] == ' ' || data[currentIndex]=='\t' || data[currentIndex] == '\r' || data[currentIndex] == '\n') break;
			s += String.valueOf(data[currentIndex]);
			
		}
		if (currentIndex == data.length) {
			token =  new Token(TokenType.EOF, null);
		}
		else if(s.length() >= 1) {
			token = new Token(TokenType.EOF, s);
		}
		else {
			token = new Token(TokenType.SYMBOL, data[currentIndex]);
		}
		return token; // returns to nextToken();
	}
	
	/**
	 * Can be called multiple times, doesn't generate new token
	 * @return last generated token
	 */
	public Token getToken() {
		return token;
	}
	
	/**
	 * helper method to skip blanks, new lines etc.
	 */
	
	private void skipBlanks() { //inspired by Book, prof. Cupic
        while (currentIndex<data.length) {
        	char k = data[currentIndex];
        	if(k==' ' || k=='\t' || k=='\r' || k=='\n') {
        		currentIndex++;
        		continue;
        	}
        	break;
        }
    }
}


