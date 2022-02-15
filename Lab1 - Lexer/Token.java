package hr.fer.oprpp1.hw02.prob1;

/**
 * @author Dominik
 * Represents one token generated by our Lexer class
 */
public class Token {
	/**
	 * token type
	 */
	private TokenType type;
	/**
	 * value of token
	 */
	private Object value;
	
	/**
	 * sets type and value of this token
	 * @param type
	 * @param value
	 */
	public Token(TokenType type, Object value) {
		this.type = type;
		this.value = value;
	}
	/**
	 * @return value of this token
	 */
	public Object getValue() {
		return value;
	}
	/**
	 * @return type of this token
	 */
	public TokenType getType() {
		return type;
	}
}