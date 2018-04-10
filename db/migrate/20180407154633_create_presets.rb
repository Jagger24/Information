class CreatePresets < ActiveRecord::Migration[5.1]
  def change
    create_table :presets do |t|
      t.string :email
      t.string :code

      t.timestamps
    end
  end
end
