class CreateAttempts < ActiveRecord::Migration[5.1]
  def change
    create_table :attempts do |t|
      t.string :content
      t.integer :user_id

      t.timestamps
    end
  end
end
