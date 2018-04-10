class AddEmailToPtokens < ActiveRecord::Migration[5.1]
  def change
    add_column :ptokens, :email, :string
  end
end
