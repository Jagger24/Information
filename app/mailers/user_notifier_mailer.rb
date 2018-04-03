class UserNotifierMailer < ApplicationMailer
	default :from => '4471noreply@gmail.com'

	def send_email(user, code)
		@code = code
		mail( :to => user.email)
	end

	def token_email(user, codes)
		@code = codes
		mail( :to => user.email)
	end
end
