class RenameEmailToUserId < ActiveRecord::Migration[5.1]
  def change
  	rename_column :tokens, :email, :user_id
  end
end
