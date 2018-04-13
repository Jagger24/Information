Rails.application.routes.draw do
  resources :presets
  resources :attempts
  devise_for :users, controllers: {registration: "user/registrations"}
  get 'welcome/index'
  get 'welcome/profile'
  get 'welcome/notice'
  get 'welcome/password'
  root 'welcome#index'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
