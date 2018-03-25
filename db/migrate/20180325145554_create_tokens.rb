class CreateTokens < ActiveRecord::Migration[5.1]
  def change
    create_table :tokens do |t|
      t.string :email
      t.string :code

      t.timestamps
    end
  end
end
