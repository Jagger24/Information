class WelcomeController < ApplicationController
  def index
  	if user_signed_in?
  		@mail = current_user.email
  	end

  end
end
