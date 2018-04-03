class UserNotifierMailer < ApplicationMailer
	default :from => 'jaggerjeffrey@gmail.com'

	def send_email
		#@user = current_user
		mail( :to => 'jaggerjeffrey@gmail.com')
	end
end
