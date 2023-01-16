import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoggedInGuard } from './grd/logged-in.guard';
import { LoggedOutGuard } from './grd/logged-out.guard';
import { HomeComponent } from './ui/page/home.component';
import { LoginComponent } from './ui/page/login.component';
import { ProfileComponent } from './ui/page/profile.component';
import { RegisterComponent } from './ui/page/register.component';

const routes: Routes = [
  {path: 'login', component: LoginComponent, canActivate: [LoggedOutGuard]},
  {path: 'register', component: RegisterComponent, canActivate: [LoggedOutGuard]},
  {path: 'profile', component: ProfileComponent, canActivate: [LoggedInGuard]},
  {path: '', component: HomeComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
