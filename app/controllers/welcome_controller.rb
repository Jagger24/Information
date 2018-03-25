class WelcomeController < ApplicationController
  def index
  	if user_signed_in?
  		@test = Attempt.find_by user_id: current_user.id
  	
  		if @test.nil?
  			redirect_to "/attempts/new"
  		
  		end
  	end
  	if !@test.nil?
	  	if user_signed_in?
	  		@token = Token.find_by user_id: current_user.id
	  		if @token.nil?
	  			@token = Token.new
	  			@token.code = 1
	  		end
	  		@token_code = @token.code
	  		@attempt = Attempt.find_by user_id: current_user.id
	  		@attempt_code = @attempt.content

	  	

	  		if @token_code == @attempt_code
	  			@mail = current_user.email
	  			Token.where(:user_id => current_user.id).destroy_all
	  		else 
	  			redirect_to "/attempts/new"
	  		end 
	 	 end
 	end
  end
end
