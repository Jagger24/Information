class DropPresetsTable < ActiveRecord::Migration[5.1]
  def up
  	drop_table :presets
  end
end
