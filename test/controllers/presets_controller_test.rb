require 'test_helper'

class PresetsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @preset = presets(:one)
  end

  test "should get index" do
    get presets_url
    assert_response :success
  end

  test "should get new" do
    get new_preset_url
    assert_response :success
  end

  test "should create preset" do
    assert_difference('Preset.count') do
      post presets_url, params: { preset: { code: @preset.code, email: @preset.email } }
    end

    assert_redirected_to preset_url(Preset.last)
  end

  test "should show preset" do
    get preset_url(@preset)
    assert_response :success
  end

  test "should get edit" do
    get edit_preset_url(@preset)
    assert_response :success
  end

  test "should update preset" do
    patch preset_url(@preset), params: { preset: { code: @preset.code, email: @preset.email } }
    assert_redirected_to preset_url(@preset)
  end

  test "should destroy preset" do
    assert_difference('Preset.count', -1) do
      delete preset_url(@preset)
    end

    assert_redirected_to presets_url
  end
end
