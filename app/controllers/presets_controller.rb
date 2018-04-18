#AUTHOR Jeff and Abdi
class PresetsController < ApplicationController
  before_action :set_preset, only: [:show, :edit, :update, :destroy]

  # GET /presets
  # GET /presets.json
  def index
    @presets = Preset.all
    #this is an administrative page used to test and see all attempts from users
  end

  # GET /presets/1
  # GET /presets/1.json
  def show
  end

  # GET /presets/new
  def new
    @preset = Preset.new
    #This is the page that useres see to create a new attempt
  end

  # GET /presets/1/edit
  def edit
  end

  # POST /presets
  # POST /presets.json
  def create
    #grab the info that the user entered in
    @preset = Preset.new(preset_params) 
    
      if @preset.save #if the preset saved correctly
   
        #find the user by their email because they are not logged in
        @use = User.find_by email: @preset.email

        #if the user entered in a proper email
        if !@use.nil?
          #take the code that they created and encrypt it
          @testCode = encrypt(@preset.code, @use.id, "-e")

          #after it is encrypted try to find a similar encrypted code with their user id
          @ptoken = Ptoken.where(:user_id => @use.id, :code => @testCode)

          #check the length of ptoken array
          size = @ptoken.length
          if size == 0
              #SEND TO AN ERROR PAGE
              redirect_to "/welcome/password"
          else

            #if there is an existing encrypted token that matches the entry.
            #then destroy that code as it is a one time use
            Ptoken.where(:user_id => @use.id, :code => @testCode).destroy_all
            #send the user a reset password instruction email!
            @use.send_reset_password_instructions

            #reditect them to the notice about the email being sent
            redirect_to "/welcome/notice"
           

          end
        end
        
      else
        format.html { render :new }
        format.json { render json: @preset.errors, status: :unprocessable_entity }
      end
    
  end

  # PATCH/PUT /presets/1
  # PATCH/PUT /presets/1.json
  def update
    respond_to do |format|
      if @preset.update(preset_params)
        format.html { redirect_to @preset, notice: 'Preset was successfully updated.' }
        format.json { render :show, status: :ok, location: @preset }
        
        redirect_to "/welcome/notice_pwchange"
      else
        format.html { render :edit }
        format.json { render json: @preset.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /presets/1
  # DELETE /presets/1.json
  def destroy
    @preset.destroy
    respond_to do |format|
      format.html { redirect_to presets_url, notice: 'Preset was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_preset
      @preset = Preset.find(params[:id])
      #set the params that the user set
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def preset_params
      params.require(:preset).permit(:email, :code)
      #get the parameteres from the user
    end

  #This function will be used to encrypt the codes that the users enter in
  #The controller will then compare the encrypted codes to eachother.
  def encrypt(code, key, flag)
    output = '~/4471/information/encrypt/encryption.exe #{code} #{key} #{flag}'
    output = %x[~/4471/information/encrypt/encryption.exe #{code} #{key} #{flag}]
    return output


  end
   
end
