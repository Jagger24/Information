class WelcomeController < ApplicationController
  def index

  	if user_signed_in?
  		redirect_to "/attempts/new"
  		@mail = current_user.email
  	end

  end
end
