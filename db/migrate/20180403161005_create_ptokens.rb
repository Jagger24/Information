class CreatePtokens < ActiveRecord::Migration[5.1]
  def change
    create_table :ptokens do |t|
      t.integer :user_id
      t.string :code

      t.timestamps
    end
  end
end
