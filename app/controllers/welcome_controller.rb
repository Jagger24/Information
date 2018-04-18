#AUTHOR Jeff Jagger.24
#The welcome controller holds the static pages for the site. This is where 2-factor authentication blocks views if the user has not gone through the full process yet
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
  	if !@test.nil? #ensure there is an attempt
	  	if user_signed_in? #ensure they are not bypassing the log in

        #Grab the token the user needs to enter in
	  		@token = Token.find_by user_id: current_user.id

	  		#check an error case so that nil errors do not occur
	  		if @token.nil?
	  			@token = Token.new
	  			@token.code = 1
	  		end

        #This method creates a new process in c in which decrypts the stored code to compare it to the users entry
	  		@token_code = encrypt(@token.code, current_user.id, "-d")

        #grab the attempt the user had made
	  		@attempt = Attempt.find_by user_id: current_user.id

        #set the code to what was found from the query (so that it is not an array and just a string)
	  		@attempt_code = @attempt.content
	       
	  	
	  		#if they entered the correct attempt, delete the token and allow them to move on
	  		if @token_code == @attempt_code
	  			@mail = current_user.email

          #destroy the 1 time token as the user has now used it
	  			Token.where(:user_id => current_user.id).destroy_all 
         #redirect them to their static profile!
          redirect_to "/welcome/profile"
	  		#if their attempt was incorrect, let them try again
	  		else 
	  			redirect_to "/attempts/new" #redirect them back to the attempt page
	  		end 
	 	 end
 	end
  end
  #user profile page
  def profile
  	@user = current_user #grab the user that is currently logged in
  end
  #notify user email was sent to change password
  def notice
    #
  end
  #notify password change
  	def notice_pwchange
    end

  def password
  end


  #This is the function that will encrypt or decrypt codes
  #it calls an exe file
  #For this controller it will only decrypt codes and not encrypt them
  def encrypt(code, key, flag)
    output = '~/4471/information/encrypt/encryption.exe #{code} #{key} #{flag}'
    output = %x[~/4471/information/encrypt/encryption.exe #{code} #{key} #{flag}]
    return output


  end
  
end
