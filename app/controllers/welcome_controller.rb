class WelcomeController < ApplicationController
  def index
  	#check if the user is signed in or not
  	#if they are not signed in, show them the welcome screen to sign up or log in
  	if user_signed_in?
  		#check if they are attempting to log in 2-factored
  		@test = Attempt.find_by user_id: current_user.id 
  		#if they havent attempted a check yet, let them
  		if @test.nil?
  			redirect_to "/attempts/new"
  		
  		end
  	end
  	#if the user has entered an attempt, check it
  	if !@test.nil?
	  	if user_signed_in?
	  		@token = Token.find_by user_id: current_user.id
	  		#check an error case so that nil errors do not occur
	  		if @token.nil?
	  			@token = Token.new
	  			@token.code = 1
	  		end
	  		@token_code = @token.code
	  		@attempt = Attempt.find_by user_id: current_user.id
	  		@attempt_code = @attempt.content
	  		#grab the users attempts
	  	
	  		#if they entered the correct attempt, delete the token and allow them to move on
	  		if @token_code == @attempt_code
	  			@mail = current_user.email
	  			Token.where(:user_id => current_user.id).destroy_all
	  		#if their attempt was incorrect, let them try again
	  		else 
	  			redirect_to "/attempts/new"
	  		end 
	 	 end
 	end
  end
  def show
  end
end
