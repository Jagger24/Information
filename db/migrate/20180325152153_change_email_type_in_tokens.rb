class ChangeEmailTypeInTokens < ActiveRecord::Migration[5.1]
  def change
  	change_column :tokens, :email, :integer
  end
end
