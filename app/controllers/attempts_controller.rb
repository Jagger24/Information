class AttemptsController < ApplicationController
  before_action :set_attempt, only: [:show, :edit, :update, :destroy]

  # GET /attempts
  # GET /attempts.json
  def index
    @attempts = Attempt.all
  end

  # GET /attempts/1
  # GET /attempts/1.json
  def show
  end

  # GET /attempts/new
  def new
    @test = Token.find_by user_id: current_user.id
    Attempt.where(:user_id => current_user.id).destroy_all #important CHANGE FOR SPECIFIC USER
    if @test.nil?
      @token = Token.new
      @token.user_id = current_user.id
      @token.code = random_hash(6)
      @token.save

      #current_user might not be right
      UserNotifierMailer.send_email.deliver
 
    end
    #CREATE THE HASHING FUNCTION HERE TO SEND USER THE COE!!!
    
    @test = Token.find_by user_id: current_user.id
    @attempt = Attempt.new
  end

  # GET /attempts/1/edit
  def edit
  end

  # POST /attempts
  # POST /attempts.json
  def create
    @attempt = Attempt.new(attempt_params)
    @attempt.user_id = current_user.id

    #respond_to do |format|
      if @attempt.save
        #format.html { redirect_to @attempt, notice: 'Attempt was successfully created.' }
        #format.json { render :show, status: :created, location: @attempt }
        redirect_to "/welcome/index"
      else
        format.html { render :new }
        format.json { render json: @attempt.errors, status: :unprocessable_entity }
      end
    #end
  end

  # PATCH/PUT /attempts/1
  # PATCH/PUT /attempts/1.json
  def update
    respond_to do |format|
      if @attempt.update(attempt_params)
        format.html { redirect_to @attempt, notice: 'Attempt was successfully updated.' }
        format.json { render :show, status: :ok, location: @attempt }
      else
        format.html { render :edit }
        format.json { render json: @attempt.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /attempts/1
  # DELETE /attempts/1.json
  def destroy
    @attempt.destroy
    respond_to do |format|
      format.html { redirect_to attempts_url, notice: 'Attempt was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_attempt
      @attempt = Attempt.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def attempt_params
      params.require(:attempt).permit(:content)
    end

   
	#Hash Code Function
	def random_hash(number)

	   hash = ""

  	#create pool of characters to draw from
  	upalpha = ('A'..'Z').to_a
  	lowalpha = ('a'..'z').to_a
  	num =('1'..'9').to_a
  	charset = upalpha + lowalpha + num 

  	#used to limit length of hashcode that's generated
  	count = 0

  	#While Loop to Create Hash Function
  	while count < number do
    	hash = hash + charset.sample
    	count += 1
	   end

	#print Hashcode as string
	return hash

	#end method
	end
   

end
